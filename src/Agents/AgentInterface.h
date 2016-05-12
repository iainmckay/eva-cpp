#ifndef EVA_AGENTS_AGENTINTERFACE_H
#define EVA_AGENTS_AGENTINTERFACE_H

#include "../Statistics.h"

class AgentInterface
{

    public:
        virtual ~AgentInterface()
        {
        }

        virtual bool hasActiveClient(const int capabilities) const = 0;
        virtual void tick() = 0;
        virtual void broadcastFrame(const FrameStatistics statistics) = 0;
};

#endif /* EVA_AGENTS_AGENTINTERFACE_H */
