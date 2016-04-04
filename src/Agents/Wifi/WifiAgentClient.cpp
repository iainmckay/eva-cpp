#include "WifiAgentClient.h"

WifiAgentClient::WifiAgentClient(const WifiAgent* agent, const IPAddress addr, const int port) :
        _status(WifiAgentClient::STATUS_CONNECTING)
{
    _agent = agent;
    _addr = addr;
    _port = port;
}

bool WifiAgentClient::isActive() const
{
    return true;
}

void WifiAgentClient::disconnect(int reason)
{
    _status = WifiAgentClient::STATUS_DISCONNECTED;
}
