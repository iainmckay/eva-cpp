#include "AgentManager.h"
#include "Wifi/WifiAgent.h"

AgentManager::AgentManager(const LoggerInterface *logger)
{
    _logger = logger;
    _logger->writeln(LOG_INFO, "agent_manager", "agent manager initializing");
    _logger->writeln(LOG_INFO, "agent_manager", "...adding wifi agent");

    _agents.push_back(std::unique_ptr<WifiAgent>(new WifiAgent(_logger)));
}

void AgentManager::tick()
{
    // TODO: mixing

    for (auto it(_agents.begin()), ite(_agents.end()); it != ite; ++it) {
        (*it)->tick();
        _inputFrame = (*it)->getInputFrame();
    }
}

bool AgentManager::hasActiveClient(const int capabilities) const
{
    bool has = false;

    for (auto it(_agents.begin()), ite(_agents.end()); it != ite; ++it) {
        if ((*it)->hasActiveClient(capabilities) == true) {
            has = true;
            break;
        }
    }

    return has;
}

InputFrame AgentManager::getInputFrame() const
{
    return _inputFrame;
}

void AgentManager::broadcastFrame(const FrameStatistics frame)
{
    for (auto it(_agents.begin()), ite(_agents.end()); it != ite; ++it) {
        (*it)->broadcastFrame(frame);
    }
}
