#ifndef __LOG_H
#define __LOG_H

#include <string>
#include <iostream>

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#define LOG(message) osoasso::log(message)
#else
#define LOG(message)
#endif

namespace osoasso
{

void log(const std::string& message);

}

#endif // __LOG_H
