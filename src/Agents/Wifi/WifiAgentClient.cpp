#include "WifiAgentClient.h"

WifiAgentClient::WifiAgentClient(const IPAddress addr, const int port, const int capabilities) :
        _state(WifiAgentClient::STATE_CONNECTED)
{
    _addr = addr;
    _port = port;
    _capabilities = capabilities;
}

IPAddress WifiAgentClient::getAddress() const
{
    return _addr;
}

int WifiAgentClient::getPort() const
{
    return _port;
}

bool WifiAgentClient::isActive() const
{
    return (_state == STATE_CONNECTED);
}

bool WifiAgentClient::supports(int mask) const
{
    return ((_capabilities & mask) == mask);
}

void WifiAgentClient::disconnect(int reason)
{
    _state = WifiAgentClient::STATE_DISCONNECTED;
    _disconnectReason = reason;
}
