#ifndef EVA_AGENTS_AGENTMANAGER_H
#define EVA_AGENTS_AGENTMANAGER_H

#include "../eva.h"
#include "../Statistics.h"
#include "AgentInterface.h"
#include "AgentClientInterface.h"

class AgentManager
{

    private:
        const LoggerInterface *_logger;
        std::vector<std::unique_ptr<AgentInterface>> _agents;

    public:
        AgentManager(const LoggerInterface *logger);

        bool hasActiveClient(int capabilities = CAP_ANY) const;
        void tick();
        void broadcastFrame(const FrameStatistics frame);
};

#endif /* EVA_AGENTS_AGENTMANAGER_H */
