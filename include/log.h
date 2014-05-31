#ifndef __LOG_H
#define __LOG_H

#include <string>
#include <iostream>
#include <pthread.h>

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define LOG(message) osoasso::logger::log(message)
#else
#define LOG(message)
#endif

namespace osoasso
{

class logger
{
public:
    static void log(const std::string& message);

private:
    static pthread_mutex_t mutex_;
};

}

#endif // __LOG_H
