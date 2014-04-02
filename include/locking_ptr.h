#ifndef __LOCKING_PTR_H
#define __LOCKING_PTR_H

namespace osoasso
{

// From Andrei Alexandrescu in Dr. Dobbs: http://drdobbs.com/cpp/184403766
template<typename T>
class locking_ptr
{
public:
    locking_ptr(volatile T& object_to_lock, pthread_mutex_t& mutex) :
        locked_object_(const_cast<T*>(&object_to_lock)), lock_(&mutex)
    {
    }

    T& operator*()
    {
        return *locked_object_;
    }

    T* operator->()
    {
        return locked_object_;
    }
    
private:
    T* locked_object_;
    scoped_lock lock_;

    locking_ptr(const locking_ptr&);
    locking_ptr& operator=(const locking_ptr&);
};

}

#endif // __LOCKING_PTR_H
