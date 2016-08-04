#include "SpeedControllerManager.h"

SpeedControllerManager::SpeedControllerManager()
{
    _speedControllerCount = 4;

    analogWriteFreq(50);
    analogWriteRange(1000);
}

void SpeedControllerManager::arm()
{
    _enabled = true;
}

void SpeedControllerManager::adjustSpeed(const uint index, const float amount)
{
    _speedControllers[index].changeSpeed(amount);
}

void SpeedControllerManager::tick()
{
    SpeedController *controller;

    if (_enabled == false) {
        return;
    }

    for (uint i = 0; i < _speedControllerCount; i++) {
        _speedControllers[i].tick();
    }
}

const uint SpeedControllerManager::getControllerCount()
{
    return _speedControllerCount;
}

const float SpeedControllerManager::getControllerSpeed(const uint index)
{
    return _speedControllers[index].getSpeed();
}

const int SpeedControllerManager::getControllerStatus(const uint index)
{
    return _speedControllers[index].getStatus();
}
