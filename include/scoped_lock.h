#ifndef __SCOPED_LOCK_H
#define __SCOPED_LOCK_H

#include <pthread.h>

namespace osoasso
{

class scoped_lock
{
public:
    explicit scoped_lock(pthread_mutex_t* mutex) : mutex_(mutex)
    {
        if (!pthread_mutex_lock(mutex_))
        {
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
