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
#include <sstream>
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"
#include "../include/scoped_lock.h"
#include "../include/locking_ptr.h"
#include "../include/string_splitter.h"
#include "../include/log.h"

namespace osoasso
{

const int post_message_max_string_length_ = 65000;

class OsoassoInstance : public pp::Instance
{
public:
    explicit OsoassoInstance(PP_Instance pp_instance) : pp::Instance(pp_instance), instance(manager)
    {
        LOG("Starting OsoassoInstance constructor");
        // Don't check the error code, it seems that it is non-zero even on success.
        pthread_mutex_init(&message_mutex_, NULL);
        LOG("Completed OsoassoInstance constructor");
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
                *locked_message = instance.handle_message(*locked_message);
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

        osoasso::string_splitter splitter(*locked_message, post_message_max_string_length_);
        for (int i = 0; i < splitter.number_of_parts(); ++i)
        {
            std::stringstream part_indicator;
            part_indicator << i + 1 << "," << splitter.number_of_parts() << "," << splitter.part(i);
            instance->PostMessage(pp::Var(part_indicator.str()));
        }
    }
};

class OsoassoModule : public pp::Module
{
public:
    OsoassoModule() : pp::Module() {}
    virtual ~OsoassoModule() {}

    virtual pp::Instance* CreateInstance(PP_Instance instance)
    {
        LOG("Starting CreateInstance");

        auto osoasso_app = new OsoassoInstance(instance);

        LOG("Completing CreateInstance");
        return osoasso_app;
    }
};

}  // namespace osoasso

namespace pp
{

Module* CreateModule()
{
    LOG("Starting CreateModule");
    auto module = new osoasso::OsoassoModule();

    LOG("Completing CreateModule");
    return module;
}

}  // namespace pp

