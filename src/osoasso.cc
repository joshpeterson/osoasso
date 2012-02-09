#include <ppapi/cpp/dev/scriptable_object_deprecated.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>
#include <ppapi/cpp/core.h>
#include <ppapi/cpp/completion_callback.h>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <deque>
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"

namespace osoasso
{

// Keep the lock class in this file so that it doesn't get used elsewhere (keep the threading exposure small)
class scoped_lock
{
public:
    explicit scoped_lock(pthread_mutex_t mutex) : mutex_(&mutex)
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

// From Andrei Alexandrescu in Dr. Dobbs: http://drdobbs.com/cpp/184403766
template<typename T>
class locking_ptr
{
public:
    locking_ptr(volatile T& object_to_lock, pthread_mutex_t& mutex) :
        locked_object_(const_cast<T*>(&object_to_lock)), lock_(mutex)
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

class OsoassoInstance : public pp::Instance
{
public:
    explicit OsoassoInstance(PP_Instance instance) : pp::Instance(instance), instance(manager)
    {
        // Don't check the error code, it seems that it is non-zero even on success.
        pthread_mutex_init(&message_mutex_, NULL);
    }

    virtual ~OsoassoInstance()
    {
        pthread_join(command_thread_, NULL);
        pthread_mutex_destroy(&message_mutex_);
    }

    virtual void HandleMessage(const pp::Var& var_message);

private:
    project_manager manager;
    osoasso_instance instance;

    pthread_t command_thread_;
    pthread_mutex_t message_mutex_;
    volatile std::string message_;

    void RunCommand();

    static void* CallRunCommand(void* This)
    {
        static_cast<OsoassoInstance*>(This)->RunCommand();
        return NULL;
    }

    static void PostMessageCallback(void* This, int32_t /*result*/)
    {
        OsoassoInstance* instance = static_cast<OsoassoInstance*>(This);
        locking_ptr<std::string> locked_message(instance->message_, instance->message_mutex_);
        instance->PostMessage(pp::Var(*locked_message));
    }
};

void OsoassoInstance::HandleMessage(const pp::Var& var_message)
{
    if (!var_message.is_string())
    {
        return;
    }

    std::string message = var_message.AsString();

    locking_ptr<std::string> locked_message(message_, message_mutex_);
    *locked_message = message;

    pthread_create(&command_thread_, NULL, &CallRunCommand, this);
}

void OsoassoInstance::RunCommand()
{
    {
        locking_ptr<std::string> locked_message(message_, message_mutex_);
        try
        {
            message_output output = instance.handle_message(*locked_message);

            if (output.type == message_output_string)
            {
                *locked_message = output.value.commit_string;
            }
            else
            {
                // Only handle strings for now.
            }
        }
        catch (std::exception& e)
        {
            *locked_message = e.what();
        }
    }

    pp::Core* core = pp::Module::Get()->core();
    core->CallOnMainThread(0, pp::CompletionCallback(PostMessageCallback, this));
}

class OsoassoModule : public pp::Module
{
public:
    OsoassoModule() : pp::Module() {}
    virtual ~OsoassoModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance)
    {
        return new OsoassoInstance(instance);
    }
};

}  // namespace osoasso

namespace pp
{

Module* CreateModule()
{
    return new osoasso::OsoassoModule();
}

}  // namespace pp

