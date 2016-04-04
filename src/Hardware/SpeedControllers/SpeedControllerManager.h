#ifndef EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H
#define EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H

#include "SpeedController.h"

class SpeedControllerManager
{
private:
    bool _enabled;
    uint _speedControllerCount;
    SpeedController _speedControllers[4] = {
        SpeedController(0, 0, 0, 0),
        SpeedController(0, 0, 0, 0),
        SpeedController(0, 0, 0, 0),
        SpeedController(0, 0, 0, 0)
    };

public:
    SpeedControllerManager();

    void adjustThrottle(uint index, float amount);
    void arm();
    void tick();
};

#endif /* EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H */
