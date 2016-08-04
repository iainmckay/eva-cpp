#ifndef EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H
#define EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H

#include "SpeedController.h"

class SpeedControllerManager
{
    private:
        bool _enabled;
        uint _speedControllerCount;
        SpeedController _speedControllers[4] = {
                /*SpeedController(800, 2000, 2000, 16),
                SpeedController(800, 2000, 2000, 14),
                SpeedController(800, 2000, 2000, 13),
                SpeedController(800, 2000, 2000, 12)*/
                SpeedController(000, 1000, 2000, 16),
                SpeedController(0, 1000, 2000, 14),
                SpeedController(0, 1000, 2000, 13),
                SpeedController(0, 1000, 2000, 12)
        };

    public:
        SpeedControllerManager();

        void adjustSpeed(const uint index, const float amount);
        void arm();
        void tick();

        const uint getControllerCount();
        const float getControllerSpeed(const uint index);
        const int getControllerStatus(const uint index);
};

#endif /* EVA_HARDWARE_SPEEDCONTROLLERS_SPEEDCONTROLLERMANAGER_H */
