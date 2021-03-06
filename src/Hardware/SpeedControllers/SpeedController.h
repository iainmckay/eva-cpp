#ifndef EVA_HARDWARE_SPEEDCONTROLLERS_MYSTERY_MYSTERYSPEEDCONTROLLER_H
#define EVA_HARDWARE_SPEEDCONTROLLERS_MYSTERY_MYSTERYSPEEDCONTROLLER_H

#include "../../eva.h"

class SpeedController
{
    private:
        uint _pin;
        uint _minRange;
        uint _maxRange;
        uint _armingTime;
        float _amount;

        ulong _armingTimer;
        bool _armed;

    public:
        SpeedController(const uint minRange, const uint maxRange, const uint armingTime, const uint pin);

        void changeSpeed(const float value);
        void tick();
        const float getSpeed();
        const int getStatus();

    private:
        const uint map(const float value) const;
};

#endif /* EVA_HARDWARE_SPEEDCONTROLLERS_MYSTERY_MYSTERYSPEEDCONTROLLER_H */
