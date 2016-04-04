#ifndef EVA_AGENTS_WIFI_WIFIAGENT_H
#define EVA_AGENTS_WIFI_WIFIAGENT_H

#include "../../eva.h"
#include "../AgentInterface.h"
#include "WifiAgentClient.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "utility/socket.h"

// FIXME: make configurable
#define WIFI_SSID "MCKAY-O"
#define WIFI_KEY "30292822"
#define WIFI_PORT 2976
#define WIFI_BUFFER_LENGTH 128

#define MSG_UNKNOWN 0
#define MSG_HELLO 1
#define MSG_WELCOME 2
#define MSG_PING 3
#define MSG_PONG 4

struct BaseMessage;
struct HelloMessage;

class WifiAgent : public AgentInterface
{
    private:
        int _status;
        const LoggerInterface *_logger;
        std::vector<std::shared_ptr<WifiAgentClient>> _clients;

        WiFiUDP _socket;
        byte _buffer[WIFI_BUFFER_LENGTH];

    public:
        WifiAgent(const LoggerInterface *logger);

        void tick();
        bool hasActiveClient(const int capabilities) const;

    private:
        void onConnectedAP();

        void onHelloMessage(const std::shared_ptr<WifiAgentClient> client,
                            const HelloMessage *msg,
                            const IPAddress remoteAddr,
                            const int remotePort);

        void handleWifi();

        void handleNetwork();

        const std::shared_ptr<WifiAgentClient> findClient(const IPAddress addr, const int port) const;

        BaseMessage createMessage(const byte buffer[WIFI_BUFFER_LENGTH], const int length) const;
};

struct BaseMessage
{
    byte type = MSG_UNKNOWN;

    virtual int expectedSize() const
    {
        return 1;
    }
};

struct HelloMessage : BaseMessage
{
    unsigned short capabilities;

    int expectedSize() const
    {
        return 3;
    }
};

#endif /* EVA_AGENTS_WIFI_WIFIAGENT_H */
