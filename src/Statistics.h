#ifndef EVA_STATISTICS_H
#define EVA_STATISTICS_H

struct FrameStatistics
{

    public:
        // when the frame end time is captured, we still have to dispatch the frame to any telemetry listeners
        // this value holds the time spent in that phase
        byte overhead;
        ulong start;
        byte length;
        byte agent;
        byte drone;

        byte motorCount;
        byte motorStatus[4];
        byte motorLevels[4];
};

#endif /* EVA_STATISTICS_H */
