#include "SpeedController.h"
#include "../../Drone.h"

SpeedController::SpeedController(const uint minRange, const uint maxRange, const uint armingTime, const uint pin)
{
    _minRange = minRange;
    _maxRange = maxRange;
    _armingTime = armingTime;
    _pin = pin;
    _armed = false;
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
            Serial.printf("arming %d\n", _pin);
            value = _maxRange;
        } else if ((_armingTimer - millis()) >= _armingTime) {
            Serial.printf("armed %d\n", _pin);
            value = _minRange;

            _armed = true;
        }
    } else {
        value = map(_amount);
    }

    analogWrite(_pin, value);
}

const uint SpeedController::map(const float value) const
{
    return (uint) (((_maxRange - _minRange) * value) + _minRange);
}

const float SpeedController::getSpeed()
{
    return _amount;
}

const int SpeedController::getStatus()
{
    if (_armed == true) {
        return MOTOR_STATUS_CONNECTED;
    } else if ((_armed == false) && (_armingTimer > 0)) {
        return MOTOR_STATUS_ARMING;
    } else if ((_armed == false) && (_armingTimer == 0)) {
        return MOTOR_STATUS_NOTARMED;
    } else {
        return MOTOR_STATUS_MISSING;
    }
}
