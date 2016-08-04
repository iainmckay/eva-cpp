#ifndef EVA_AGENTS_WIFI_WIFIAGENT_H
#define EVA_AGENTS_WIFI_WIFIAGENT_H

#include "../../eva.h"
#include "../../InputFrame.h"
#include "../AgentInterface.h"
#include "WifiAgentClient.h"
#include "../../Statistics.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// FIXME: make configurable
#define WIFI_SSID "MCKAY-O"
#define WIFI_KEY "30292822"
//#define WIFI_SSID "myschool_wifi"
//#define WIFI_KEY "letmein2"
#define WIFI_PORT 2976
#define WIFI_BUFFER_LENGTH 128

#define MSG_UNKNOWN 0
#define MSG_HELLO 1
#define MSG_WELCOME 2
#define MSG_PING 3
#define MSG_PONG 4
#define MSG_FRAME 5
#define MSG_INPUT 6

struct BaseMessage;
struct HelloMessage;
struct InputMessage;
struct WelcomeMessage;

class WifiAgent : public AgentInterface
{
    private:
        int _status;
        const LoggerInterface *_logger;
        std::vector<std::shared_ptr<WifiAgentClient>> _clients;

        WiFiUDP _socket;
        byte _buffer[WIFI_BUFFER_LENGTH];

        InputFrame _inputFrame;

    public:
        void broadcastFrame(const FrameStatistics statistics);
        WifiAgent(const LoggerInterface *logger);

        void tick();
        bool hasActiveClient(const int capabilities) const;
        InputFrame getInputFrame() const;

    private:
        void onConnectedAP();

        void onHelloMessage(const std::shared_ptr<WifiAgentClient> client,
                            const HelloMessage msg,
                            IPAddress remoteAddr,
                            const int remotePort);

        void onInputMessage(const std::shared_ptr<WifiAgentClient> client,
                            const InputMessage msg,
                            IPAddress remoteAddr,
                            const int remotePort);

        void handleWifi();
        void handleNetwork();

        void send(const std::shared_ptr<WifiAgentClient> client, const byte *buffer, const int length);
        void sendWelcome(const std::shared_ptr<WifiAgentClient> client);

        const std::shared_ptr<WifiAgentClient> findClient(const IPAddress address, const int port) const;
};

struct BaseMessage
{
    byte type = MSG_UNKNOWN;

    virtual int expectedSize() const
    {
        return 1;
    }
};

struct HelloMessage : public BaseMessage
{
    unsigned short capabilities;

    int expectedSize() const
    {
        return 3;
    }
};

struct InputMessage : public BaseMessage
{
    float throttleLevel = 0;
    float yawLevel = 0;
    float pitchLevel = 0;
    float rollLevel = 0;

    int expectedSize() const
    {
        return 5;
    }
};

#endif /* EVA_AGENTS_WIFI_WIFIAGENT_H */
