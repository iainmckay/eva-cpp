#ifndef EVA_DRONE_H
#define EVA_DRONE_H

#include "eva.h"
#include "InputFrame.h"
#include "Hardware/SpeedControllers/SpeedControllerManager.h"

class Drone
{
    private:
        const LoggerInterface *_logger;
        std::unique_ptr<SpeedControllerManager> _escManager;

        // control inputs
        float _throttleLevel;
        float _yawLevel;
        float _pitchLevel;
        float _rollLevel;

    public:
        Drone(const LoggerInterface *logger);

        void tick(const InputFrame input);

        const uint getMotorCount();
        const float getMotorSpeed(const uint index);
        const int getMotorStatus(const uint index);

    private:
        void setInputLevels(const float throttle, const float yaw, const float pitch, const float roll);
};

#endif /* EVA_DRONE_H */

#define MOTOR_STATUS_MISSING 0
#define MOTOR_STATUS_NOTARMED 1
#define MOTOR_STATUS_ARMING 2
#define MOTOR_STATUS_CONNECTED 3
