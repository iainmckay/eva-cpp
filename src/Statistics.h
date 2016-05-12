#ifndef EVA_STATISTICS_H
#define EVA_STATISTICS_H

struct FrameStatistics
{

    public:
        // when the frame end time is captured, we still have to dispatch the frame to any telemetry listeners
        // this value holds the time spent in that phase
        ulong overhead;
        ulong start;
        ulong end;
        ulong agentStart;
        ulong agentEnd;
        ulong droneStart;
        ulong droneEnd;
};

#endif /* EVA_STATISTICS_H */
