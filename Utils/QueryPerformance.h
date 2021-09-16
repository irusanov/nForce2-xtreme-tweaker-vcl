#pragma once

class QueryPerformance {
private:
    DWORD eax, edx;

    long GetQPCTime() {
        LARGE_INTEGER qpcTime;
        QueryPerformanceCounter(&qpcTime);
        return qpcTime.LowPart;
    }

    long GetQPCRate() {
        LARGE_INTEGER qpcRate;
        QueryPerformanceFrequency(&qpcRate);
        return qpcRate.LowPart;
    }

public:
    QueryPerformance(void) {
    }

    ~QueryPerformance(void) {
    }

    double MeasureCPUFrequency() {
        double qpcRate = GetQPCRate();
        double frequency = -1;
        int retries = 6;

        while (frequency < 0 && retries > 0) {
            Rdtsc(&eax, &edx);
            long rdtscStart = eax;
            long qpcStart = GetQPCTime();

            Sleep(50);

            Rdtsc(&eax, &edx);
            long rdtscEnd = eax;

            long rdtscElapsed = rdtscEnd - rdtscStart;
            long qpcElapsed = GetQPCTime() - qpcStart;

            // frequency = 1.0e6 * rdtscElapsed / (qpcElapsed / qpcRate) / 1000000000000;
            frequency = rdtscElapsed / (qpcElapsed / qpcRate) / 1000000;
            retries--;
        }

        if (frequency == -1)
            return 0;

        return frequency;
    }
};
