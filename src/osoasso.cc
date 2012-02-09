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
#include "../include/scoped_lock.h"
#include "../include/locking_ptr.h"

namespace osoasso
{

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

    virtual void HandleMessage(const pp::Var& var_message)
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

private:
    project_manager manager;
    osoasso_instance instance;

    pthread_t command_thread_;
    pthread_mutex_t message_mutex_;
    volatile std::string message_;

    void RunCommand()
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

