#include "WifiAgentClient.h"

WifiAgentClient::WifiAgentClient(const WifiAgent* agent, const IPAddress addr, const int port) :
        _state(WifiAgentClient::STATE_CONNECTED)
{
    _agent = agent;
    _addr = addr;
    _port = port;
}

void WifiAgentClient::disconnect(int reason)
{
    _state = WifiAgentClient::STATE_DISCONNECTED;
    _disconnectReason = reason;
}
