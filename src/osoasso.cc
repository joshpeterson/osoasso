#include <ppapi/cpp/dev/scriptable_object_deprecated.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>
#include <cstdio>
#include <string>
#include <stdexcept>
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"

namespace osoasso
{

// Keep the lock class in this file so that it doesn't get used elsewhere (keep the threading exposure small)
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

class OsoassoInstance : public pp::Instance
{
public:
    explicit OsoassoInstance(PP_Instance instance) : pp::Instance(instance), instance(manager)
    {
        if (!pthread_mutex_init(&command_mutex_, NULL))
        {
            throw std::runtime_error("Unable to create command mutex - this is a serious problem.");
        }
    }

    virtual ~OsoassoInstance()
    {
        pthread_mutex_destroy(&command_mutex_);
    }

    virtual void HandleMessage(const pp::Var& var_message);

private:
    project_manager manager;
    osoasso_instance instance;
    pthread_mutex_t command_mutex_;
};

void OsoassoInstance::HandleMessage(const pp::Var& var_message)
{
    if (!var_message.is_string())
    {
        return;
    }

    std::string message = var_message.AsString();

    try
    {
        message_output output = instance.handle_message(message);

        pp::Var return_var;
        if (output.type == message_output_string)
        {
            PostMessage(pp::Var(output.value.commit_string));
        }
        else
        {
            PostMessage(pp::Var(output.value.matrix_value));
        }
    }
    catch (std::exception& e)
    {
        PostMessage(pp::Var(e.what()));
    }
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

