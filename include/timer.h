#ifndef __TIMER_H
#define __TIMER_H

#include <ctime>

//#define USE_CLOCK_IMPLEMENTATION

#ifndef USE_CLOCK_IMPLEMENTATION
#include <sys/time.h>
#endif

namespace osoasso
{

class timer
{
public:
    timer()
    {
#ifdef USE_CLOCK_IMPLEMENTATION
        start_time_ = std::clock();
#else
        timeval time;
        gettimeofday(&time, NULL);
        start_time_value_ = time.tv_sec+(time.tv_usec/1000000.0);
#endif
        
    }

    double elapsed() const
    {
#ifdef USE_CLOCK_IMPLEMENTATION
        return double(std::clock() - start_time_) / CLOCKS_PER_SEC;
#else
        timeval time;
        gettimeofday(&time, NULL);
        double end_time_value = time.tv_sec+(time.tv_usec/1000000.0);

        return end_time_value - start_time_value_;
#endif
    }

private:
#ifdef USE_CLOCK_IMPLEMENTATION
    std::clock_t start_time_;
#else
    double start_time_value_;
#endif
};

}

#endif // __TIMER_H
