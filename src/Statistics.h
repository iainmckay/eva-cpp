#ifndef EVA_STATISTICS_H
#define EVA_STATISTICS_H

struct FrameStatistics
{

    public:
        // when the frame end time is captured, we still have to dispatch the frame to any telemetry listeners
        // this value holds the time spent in that phase
        ulong overhead;
        ulong start;
        byte length;
        byte agent;
        byte drone;
};

#endif /* EVA_STATISTICS_H */
