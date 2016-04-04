#ifndef EVA_AGENTS_AGENTINTERFACE_H
#define EVA_AGENTS_AGENTINTERFACE_H

class AgentInterface
{

public:
    virtual ~AgentInterface() {}

    virtual bool hasActiveClient(const int capabilities) const = 0;
    virtual void tick() = 0;
};

#endif /* EVA_AGENTS_AGENTINTERFACE_H */
