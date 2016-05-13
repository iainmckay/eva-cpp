#ifndef EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H
#define EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H

#include <IPAddress.h>
#include "../AgentClientInterface.h"

class WifiAgent;

class WifiAgentClient : public AgentClientInterface
{
    public:
        const static int STATE_CONNECTING = 1;
        const static int STATE_CONNECTED = 2;
        const static int STATE_DISCONNECTED = 3;

        const static int DISCONNECT_REASON_GRACEFUL = 1;
        const static int DISCONNECT_REASON_TIMEOUT = 2;
        const static int DISCONNECT_REASON_VIOLATED_ME = 3;

    private:
        int _state;
        IPAddress _addr;
        int _port;
        int _disconnectReason;
        int _capabilities;

    public:
        WifiAgentClient(const IPAddress addr, const int port, const int capabilities);

        IPAddress getAddress() const;
        int getPort() const;
        bool isActive() const;
        void disconnect(int reason);
        bool supports(int mask) const;
};


#endif /* EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H */
