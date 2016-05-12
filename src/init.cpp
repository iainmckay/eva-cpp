#include "eva.h"
#include "Logger.h"
#include "Drone.h"
#include "Statistics.h"
#include "Agents/AgentManager.h"
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

Logger *logger;
AgentManager *agentManager;
Drone *drone;

ulong timeInTransmitPhase = 0;
ulong timeLastFrameEnded = 0;

void setup()
{
    Serial.begin(115200);

    logger = new Logger();
    logger->initialize();

    agentManager = new AgentManager(logger);
    drone = new Drone(logger);

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA Error[%u]: ", error);

        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });

    ArduinoOTA.begin();
}

void loop()
{
    FrameStatistics frame;
    frame.overhead = timeInTransmitPhase - timeLastFrameEnded;
    frame.start = millis();

    ArduinoOTA.handle();

    frame.agentStart = millis();
    agentManager->tick();
    frame.agentEnd = millis();

    frame.droneStart = millis();
    drone->tick();
    frame.droneEnd = millis();

    frame.end = millis();

    agentManager->broadcastFrame(frame);
}
