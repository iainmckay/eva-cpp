#include "eva.h"
#include "Logger.h"
#include "Drone.h"
#include "Agents/AgentManager.h"

Logger* logger;
AgentManager* agentManager;
Drone* drone;

void setup()
{
    Serial.begin(115200);

    logger = new Logger();
    logger->initialize();

    agentManager = new AgentManager(logger);
    drone = new Drone(logger);
}

void loop()
{
    agentManager->tick();
}
