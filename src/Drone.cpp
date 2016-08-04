#include "Drone.h"

Drone::Drone(const LoggerInterface *logger)
        : _escManager(new SpeedControllerManager())
{
    _logger = logger;
    _logger->writeln(LOG_INFO, "drone", "arming speed controllers");

    _escManager->arm();
}

void Drone::setInputLevels(const float throttle, const float yaw, const float pitch, const float roll)
{
    _throttleLevel = constrain(throttle, 0.0f, 1.0f);
    _yawLevel = constrain(yaw, 0.0f, 1.0f);
    _pitchLevel = constrain(pitch, 0.0f, 1.0f);
    _rollLevel = constrain(roll, 0.0f, 1.0f);
    _throttleLevel = constrain(1, 0.0f, 1.0f);
    _yawLevel = constrain(1, 0.0f, 1.0f);
    _pitchLevel = constrain(1, 0.0f, 1.0f);
    _rollLevel = constrain(1, 0.0f, 1.0f);
}

void Drone::tick(const InputFrame inputFrame)
{
    setInputLevels(inputFrame.throttle, inputFrame.yaw, inputFrame.pitch, inputFrame.roll);

    float m0 = _throttleLevel;
    float m1 = _throttleLevel;
    float m2 = _throttleLevel;
    float m3 = _throttleLevel;

    float adjustBase = 0.10f;
    float pitchAdjust = adjustBase * _pitchLevel;
    float rollAdjust = adjustBase * _rollLevel;
    float yawAdjust = adjustBase * _yawLevel;

    /*if (_elevatorLevel > 0) {
     mLeft = _throttleLevel;
     mFront = _throttleLevel;
     mRear = _throttleLevel - (0.10f * _elevatorLevel);
     mRight = _throttleLevel - (0.10f * _elevatorLevel);
     } else if (_elevatorLevel < 0) {
     mLeft = _throttleLevel - (0.10f * -_elevatorLevel);
     mFront = _throttleLevel - (0.10f * -_elevatorLevel);
     mRear = _throttleLevel;
     mRight = _throttleLevel;
     }*/

     m0 = _throttleLevel - pitchAdjust - rollAdjust - yawAdjust;
     m1 = _throttleLevel - pitchAdjust + rollAdjust + yawAdjust;
     m2 = _throttleLevel + pitchAdjust + rollAdjust - yawAdjust;
     m3 = _throttleLevel + pitchAdjust - rollAdjust + yawAdjust;
m0=1;
m1=1;
m2=1;
m3=1;
    //_logger->writeln(LOG_INFO, "drone", "m0=%d m1=%d m2=%d m3=%d", m0 * 100, m1 * 100, m2 * 100, m3 * 100);

    _escManager->adjustSpeed(0, m0);
    _escManager->adjustSpeed(1, m1);
    _escManager->adjustSpeed(2, m2);
    _escManager->adjustSpeed(3, m3);

    _escManager->tick();
}

const uint Drone::getMotorCount()
{
    return _escManager->getControllerCount();
}

const float Drone::getMotorSpeed(const uint index)
{
    return _escManager->getControllerSpeed(index);
}

const int Drone::getMotorStatus(const uint index)
{
    return _escManager->getControllerStatus(index);
}
