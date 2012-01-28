#ifndef __TIMER_H
#define __TIMER_H

#include <ctime>

namespace osoasso
{

class timer
{
public:
    timer()
    {
        start_time_ = std::clock();
    }

    double elapsed() const
    {
        return double(std::clock() - start_time_) / CLOCKS_PER_SEC;
    }

private:
    std::clock_t start_time_;
};

}

#endif // __TIMER_H
