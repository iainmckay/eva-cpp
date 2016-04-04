#include "SpeedControllerManager.h"

SpeedControllerManager::SpeedControllerManager()
{
    _speedControllerCount = 4;

    analogWriteFreq(50);
    analogWriteRange(20000);
}

void SpeedControllerManager::arm()
{
    _enabled = true;
}

void SpeedControllerManager::adjustThrottle(uint index, float amount)
{
    _speedControllers[index].changeThrottle(amount);
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
