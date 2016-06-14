#include "Drone.h"

Drone::Drone(const LoggerInterface *logger)
        : _escManager(new SpeedControllerManager())
{
    _logger = logger;
    _logger->writeln(LOG_INFO, "drone", "attaching 4 speed controllers");

    //_escManager.attach(0, 16);
    /*  _escManager.attach(1, 14);
      _escManager.attach(2, 12);
      _escManager.attach(3, 13);
  */
    _logger->writeln(LOG_INFO, "drone", "arming speed controllers");

    _escManager->arm();
}

void Drone::setInputLevels(const float throttle, const float yaw, const float pitch, const float roll)
{
    _throttleLevel = constrain(throttle, 0.0f, 1.0f);
    _yawLevel = constrain(yaw, 0.0f, 1.0f);
    _pitchLevel = constrain(pitch, 0.0f, 1.0f);
    _rollLevel = constrain(roll, 0.0f, 1.0f);
}

void Drone::tick()
{
    /*Debug.Print("Entering running state");

    Stopwatch stopWatch = Stopwatch.StartNew();
    DroneFrame frame = new DroneFrame();
    DateTime lastFPSTime = DateTime.Now;
    ulong framesPerSecondCount = 0;

    while (true) {
    lock (frame) {
    // main logic loop
    frame.Timing_WholeFrame.Start();
    {
    RaiseFramePrepareEvent();


    //_escManager.DurationPercentage = _throttleLevel;

    float m0 = _throttleLevel;
    float m1 = _throttleLevel;
    float m2 = _throttleLevel;
    float m3 = _throttleLevel;

    float adjustBase = 0.10f;
    float pitchAdjust = adjustBase * _elevatorLevel;
    float rollAdjust = adjustBase * _aileronLevel;
    float yawAdjust = adjustBase * _rudderLevel;
    */
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

    /* m0 = _throttleLevel - pitchAdjust - rollAdjust - yawAdjust;
     m1 = _throttleLevel - pitchAdjust + rollAdjust + yawAdjust;
     m2 = _throttleLevel + pitchAdjust + rollAdjust - yawAdjust;
     m3 = _throttleLevel + pitchAdjust - rollAdjust + yawAdjust;

     if ((DateTime.Now - lastFPSTime).Ticks >= TimeSpan.TicksPerSecond) {
     Debug.Print("0=" + m0.ToString() + " 1=" + m1.ToString() + " 2=" + m2.ToString() + " 3=" + m3.ToString() + " P=" + pitchAdjust.ToString() + " R=" + rollAdjust.ToString() + " Y=" + yawAdjust.ToString() + " AL=" + _aileronLevel.ToString() + " RL=" + _rudderLevel.ToString() + " EL=" + _elevatorLevel.ToString());
     }
     //Debug.Print("0=" + m0.ToString() + " 1=" + m1.ToString() + " 2=" + m2.ToString() + " 3=" + m3.ToString());
     //Debug.Print("0=" + m0.ToString() + " 1=" + m1.ToString() + " 2=" + m2.ToString() + " 3=" + m3.ToString());
     _escManager._speedControllers[0].SpeedAmount = m0;
     _escManager._speedControllers[1].SpeedAmount = m1;
     _escManager._speedControllers[2].SpeedAmount = m2;
     _escManager._speedControllers[3].SpeedAmount = m3;

     frame.Stats_FrameCount++;
     }
     frame.Timing_WholeFrame.Stop();

     // calculate fps
     if ((DateTime.Now - lastFPSTime).Ticks >= TimeSpan.TicksPerSecond) {
     frame.Stats_FramesPerSecond = (ushort) (frame.Stats_FrameCount - framesPerSecondCount);
     framesPerSecondCount = frame.Stats_FrameCount;
     lastFPSTime = DateTime.Now;
     }
     }

     // let other sections of the code handle the results from a frame
     RaiseFrameCompleteEvent(frame);
     }*/
}

const uint Drone::getMotorCount()
{
    return _escManager->getControllerCount();
}

const float Drone::getMotorSpeed(const uint index)
{
    return _escManager->getControllerSpeed(index);
}
