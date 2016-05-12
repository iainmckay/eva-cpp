#include "SpeedController.h"

SpeedController::SpeedController(const uint minRange, const uint maxRange, const uint armingTime, const uint pin)
{
    _minRange = minRange;
    _maxRange = maxRange;
    _armingTime = armingTime;
    _pin = pin;
}

void SpeedController::changeSpeed(const float value)
{
    // TODO: warn when amount is outside acceptable range
    _amount = constrain(value, 0, 1);
}

void SpeedController::tick()
{
    uint value;

    if (_armed == false) {
        if (_armingTimer == 0) {
            _armingTimer = millis();
            value = _maxRange;
        } else if ((_armingTimer - millis()) >= _armingTime) {
            value = _minRange;
            _armed = true;
        }
    } else {
        value = map(_amount);
    }

    analogWrite(_pin, value);
}

uint SpeedController::map(const float value) const
{
    return (uint) (((_maxRange - _minRange) * value) + _minRange);
}
