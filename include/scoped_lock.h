#ifndef __SCOPED_LOCK_H
#define __SCOPED_LOCK_H

#include <pthread.h>
#include <sstream>
#include "../include/log.h"

namespace osoasso
{

class scoped_lock
{
public:
    explicit scoped_lock(pthread_mutex_t* mutex) : mutex_(mutex)
    {
        int error = pthread_mutex_lock(mutex_);
        if (error != 0)
        {
            std::stringstream error_message;
            error_message << "Error taking lock - error code: " << error;
            LOG(error_message.str());
            mutex_ = NULL;
        }
    }

    ~scoped_lock()
    {
        if (mutex_)
            pthread_mutex_unlock(mutex_);
    }

    bool is_valid() const
    {
        return mutex_ != NULL;
    }

private:
    pthread_mutex_t* mutex_;
};

}

#endif // __SCOPED_LOCK_H
