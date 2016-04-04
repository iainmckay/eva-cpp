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

    if (_socket.parsePacket() > 0) {
        int length = _socket.read(_buffer, WIFI_BUFFER_LENGTH);
        IPAddress remoteAddr = _socket.remoteIP();
        int remotePort = _socket.remotePort();
        const std::shared_ptr<WifiAgentClient> client = findClient(remoteAddr, remotePort);

        BaseMessage msg = createMessage(_buffer, length);

        if (msg.type == MSG_HELLO) {
            _logger->writeln(LOG_INFO, "agent.wifi", "HELLO!!!");
            //onHelloMessage(client, static_cast<HelloMessage>msg);
        }
    }
}

BaseMessage WifiAgent::createMessage(const byte buffer[WIFI_BUFFER_LENGTH], const int length) const
{
    int msgId = buffer[0];

    switch (msgId)
    {
        case MSG_HELLO:
            HelloMessage msg;

            if (msg.expectedSize() == length) {
                memcpy(&msg, buffer, length);
                return msg;
            } else {
                _logger->writeln(LOG_INFO, "agent.wifi", "got hello message of wrong length [%d received, %d expected]", length, msg.expectedSize());
            }
            break;
    }

    BaseMessage msg;
    return msg;
}

void WifiAgent::onHelloMessage(const std::shared_ptr<WifiAgentClient> client, const HelloMessage* msg,
                               const IPAddress remoteAddr,
                               const int remotePort)
{
    if (client != nullptr) {
        client->disconnect(WifiAgentClient::DISCONNECT_REASON_VIOLATED_ME);
    } else {
        WifiAgentClient* newClient = new WifiAgentClient(this, remoteAddr, remotePort);

        _clients.push_back(std::shared_ptr<WifiAgentClient>((WifiAgentClient*) newClient));
    }
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
