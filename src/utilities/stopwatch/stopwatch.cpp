#ifndef STOPWATCHCPP
#define STOPWATCHCPP

#include "stopwatch.hpp"

Stopwatch::Stopwatch()
: start(clock::now()) {};

void Stopwatch::reset(){
    start = clock::now();
}

double Stopwatch::elapsed() const{
    return sec(clock::now() - start).count();
}

#endif