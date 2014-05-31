#include "../include/log.h"
#include <pthread.h>

namespace osoasso
{

pthread_mutex_t logger::mutex_ = PTHREAD_MUTEX_INITIALIZER;

void logger::log(const std::string& message)
{
    pthread_mutex_lock(&mutex_);
    std::cout << "osoasso: " << message << std::endl;
    pthread_mutex_unlock(&mutex_);
}

}
