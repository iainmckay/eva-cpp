#ifndef EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H
#define EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H

#include <IPAddress.h>
#include "../AgentClientInterface.h"

class WifiAgent;

class WifiAgentClient : public AgentClientInterface
{
    public:
        const static int STATUS_CONNECTING = 1;
        const static int STATUS_CONNECTED = 2;
        const static int STATUS_DISCONNECTED = 3;

        const static int DISCONNECT_REASON_GRACEFUL = 1;
        const static int DISCONNECT_REASON_TIMEOUT = 2;
        const static int DISCONNECT_REASON_VIOLATED_ME = 3;

    private:
        const WifiAgent* _agent;
        int _status;
        IPAddress _addr;
        int _port;

    public:
        WifiAgentClient(const WifiAgent* agent, const IPAddress addr, const int port);

        IPAddress getAddress() const
        {
            return _addr;
        }

        int getPort() const
        {
            return _port;
        }

        bool isActive() const;
        void disconnect(int reason);
};


#endif /* EVA_AGENTS_WIFI_WIFIAGENTCLIENT_H */
