#include "WifiAgent.h"

WifiAgent::WifiAgent(const LoggerInterface *logger) :
        _status(WL_IDLE_STATUS)
{
    _logger = logger;

    if (_socket.begin(WIFI_PORT) == 0) {
        _logger->writeln(LOG_ERROR, "agent.wifi", "failed to create agent on port %d", WIFI_PORT);
    } else {
        _logger->writeln(LOG_INFO, "agent.wifi", "agent listening on port %d", WIFI_PORT);
    }

    _logger->writeln(LOG_INFO, "agent.wifi", "connecting to ap");

    WiFi.begin(WIFI_SSID, WIFI_KEY);
}

bool WifiAgent::hasActiveClient(const int capabilities) const
{
    return false;
}

InputFrame WifiAgent::getInputFrame() const
{
    return _inputFrame;
}

void WifiAgent::tick()
{
    //cleanupDisconnectedClients();
    handleWifi();
    handleNetwork();
}

void WifiAgent::handleWifi()
{
    int newStatus = WiFi.status();

    if (newStatus != _status) {
        std::string msg;

        switch (newStatus) {
            case WL_CONNECTED:
                msg = std::string("ap connected");
                break;

            case WL_CONNECT_FAILED:
                msg = std::string("ap connection failed");
                break;

            case WL_CONNECTION_LOST:
                msg = std::string("ap connection lost");
                break;

            case WL_DISCONNECTED:
                msg = std::string("ap disconnected");
                break;

            case WL_NO_SSID_AVAIL:
                msg = std::string("unknown ssid");
                break;

            default:
                msg = std::string("unknown wifi status");
                break;
        }

        _logger->writeln(LOG_INFO, "agent.wifi", msg.c_str());
        _status = newStatus;

        if (_status == WL_CONNECTED) {
            onConnectedAP();
        }
    }
}

void WifiAgent::handleNetwork()
{
    if (_status != WL_CONNECTED) {
        return;
    }

    if (_socket.parsePacket() == 0) {
        return;
    }

    int length = _socket.read(_buffer, WIFI_BUFFER_LENGTH);
    IPAddress remoteAddr = _socket.remoteIP();
    int remotePort = _socket.remotePort();
    const std::shared_ptr<WifiAgentClient> client = findClient(remoteAddr, remotePort);

    byte msgId = _buffer[0];

    switch (msgId) {
        case MSG_HELLO: {
            HelloMessage helloMsg;

            if (helloMsg.expectedSize() == length) {
                helloMsg.type = msgId;
                helloMsg.capabilities = (ushort) ((_buffer[1] << 8) + _buffer[2]);

                onHelloMessage(client, helloMsg, remoteAddr, remotePort);
            } else {
                _logger->writeln(LOG_WARNING,
                                 "agent.wifi",
                                 "got hello message of wrong length [%d received, %d expected]",
                                 length,
                                 helloMsg.expectedSize());
            }
        }
            break;

        case MSG_INPUT: {
            InputMessage inputMsg;

            if (inputMsg.expectedSize() == length) {
                inputMsg.type = msgId;
                inputMsg.throttleLevel = _buffer[1] / 100.0f;
                inputMsg.yawLevel = _buffer[2] / 100.0f;
                inputMsg.pitchLevel = _buffer[3] / 100.0f;
                inputMsg.rollLevel = _buffer[4] / 100.0f;

                onInputMessage(client, inputMsg, remoteAddr, remotePort);
            } else {
                _logger->writeln(LOG_WARNING,
                                 "agent.wifi",
                                 "got input message of wrong length [%d received, %d expected]",
                                 length,
                                 inputMsg.expectedSize());
            }
        }
            break;

        default:
            _logger->writeln(LOG_WARNING, "agent.wifi", "unknown message: %d", msgId);
            break;
    }
}

void WifiAgent::broadcastFrame(const FrameStatistics statistics)
{
    for (auto it(_clients.begin()), ite(_clients.end()); it != ite; ++it) {
        if (((*it)->isActive() == false) && ((*it)->supports(CAP_TELEMETRY) == true)) {
            continue;
        }

        uint bufferLength = (uint) (10 + (statistics.motorCount * 2));
        byte buffer[bufferLength];
        buffer[0] = MSG_FRAME;
        buffer[1] = statistics.overhead;
        buffer[2] = (byte) ((statistics.start >> 24) & 0xFF);
        buffer[3] = (byte) ((statistics.start >> 16) & 0xFF);
        buffer[4] = (byte) ((statistics.start >> 8) & 0XFF);
        buffer[5] = (byte) (statistics.start & 0XFF);
        buffer[6] = statistics.length;
        buffer[7] = statistics.agent;
        buffer[8] = statistics.drone;
        buffer[9] = statistics.motorCount;

        for (uint i = 0; i < statistics.motorCount; i++) {
            buffer[10 + i] = statistics.motorStatus[i];
        }

        for (uint i = 0; i < statistics.motorCount; i++) {
            buffer[10 + statistics.motorCount + i] = statistics.motorLevels[i];
        }

        send((*it), buffer, bufferLength);
    }
}

void WifiAgent::onHelloMessage(const std::shared_ptr<WifiAgentClient> client,
                               const HelloMessage msg,
                               IPAddress remoteAddr,
                               const int remotePort)
{
    if (client != nullptr) {
        client->disconnect(WifiAgentClient::DISCONNECT_REASON_VIOLATED_ME);
    } else {
        WifiAgentClient *ptr = new WifiAgentClient(remoteAddr, remotePort, msg.capabilities);
        std::shared_ptr<WifiAgentClient> newClient = std::shared_ptr<WifiAgentClient>(ptr);

        _clients.push_back(newClient);
        _logger->writeln(LOG_INFO, "agent.wifi", "client connected [%s:%d]", remoteAddr.toString().c_str(), remotePort);

        sendWelcome(newClient);
    }
}

void WifiAgent::onInputMessage(const std::shared_ptr<WifiAgentClient> client,
                               const InputMessage msg,
                               IPAddress remoteAddr,
                               const int remotePort)
{
    if (client != nullptr) {
        // TODO: mixing
        _inputFrame.throttle = msg.throttleLevel;
        _inputFrame.yaw = msg.yawLevel;
        _inputFrame.pitch = msg.pitchLevel;
        _inputFrame.roll = msg.rollLevel;
    }
}

void WifiAgent::sendWelcome(const std::shared_ptr<WifiAgentClient> client)
{
    byte buffer[1];
    buffer[0] = MSG_WELCOME;

    send(client, buffer, 1);
}

void WifiAgent::send(const std::shared_ptr<WifiAgentClient> client, const byte *buffer, const int length)
{
    _socket.beginPacket(client->getAddress(), client->getPort());
    _socket.write(buffer, length);
    _socket.endPacket();
}

const std::shared_ptr<WifiAgentClient> WifiAgent::findClient(const IPAddress addr, const int port) const
{
    for (auto it(_clients.begin()), ite(_clients.end()); it != ite; ++it) {
        if (((*it)->getAddress() == addr) && ((*it)->getPort() == port)) {
            return (*it);
        }
    }

    return nullptr;
}

void WifiAgent::onConnectedAP()
{
    _logger->writeln(LOG_INFO, "agent.wifi", "...ip address: %s", WiFi.localIP().toString().c_str());
}
