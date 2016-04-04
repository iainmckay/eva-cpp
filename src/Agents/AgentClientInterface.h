#ifndef EVA_AGENTS_AGENTCLIENTINTERFACE_H
#define EVA_AGENTS_AGENTCLIENTINTERFACE_H

#define CAP_TELEMETRY 1 << 1
#define CAP_CONTROL_INPUT 1 << 2
#define CAP_CONFIGURATOR 1 << 3
#define CAP_ANY CAP_TELEMETRY | CAP_CONTROL_INPUT | CAP_CONFIGURATOR

class AgentClientInterface
{

    public:
        virtual ~AgentClientInterface() {}

        virtual bool isActive() const = 0;
};

#endif /* EVA_AGENTS_AGENTCLIENTINTERFACE_H */
