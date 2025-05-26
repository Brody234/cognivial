#ifndef STOPWATCH
#define STOPWATCH

#include <chrono>

class Stopwatch {
public:
    using clock = std::chrono::high_resolution_clock;
    using sec   = std::chrono::duration<double>;

    Stopwatch();

    void reset();

    double elapsed() const;

private:
    std::chrono::time_point<clock> start;
};

#include "stopwatch.cpp"

#endif