#ifndef EVA_DRONE_H
#define EVA_DRONE_H

#include "eva.h"
#include "Hardware/SpeedControllers/SpeedControllerManager.h"

class Drone
{
    private:
        const LoggerInterface *_logger;
        SpeedControllerManager _escManager;

        // control inputs
        float _throttleLevel;
        float _yawLevel;
        float _pitchLevel;
        float _rollLevel;

    public:
        Drone(const LoggerInterface *logger);

        void setInputLevels(const float throttle, const float yaw, const float pitch, const float roll);

        void run();
};

#endif /* EVA_DRONE_H */
