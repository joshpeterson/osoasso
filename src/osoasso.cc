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

namespace osoasso
{

const int post_message_max_string_length_ = 65000;

class OsoassoInstance : public pp::Instance
{
public:
    explicit OsoassoInstance(PP_Instance pp_instance) : pp::Instance(pp_instance), instance(manager)
    {
#if !defined(__EMSCRIPTEN__)
        // Don't check the error code, it seems that it is non-zero even on success.
        pthread_mutex_init(&message_mutex_, NULL);
#endif
    }

    virtual ~OsoassoInstance()
    {
#if !defined(__EMSCRIPTEN__)
        pthread_join(command_thread_, NULL);
        pthread_mutex_destroy(&message_mutex_);
#endif
    }

    virtual void HandleMessage(const pp::Var& var_message)
    {
        //PostMessage(std::string("1,1,text#help#Looking good"));
        //return;
        if (!var_message.is_string())
        {
            return;
        }

        std::string message = var_message.AsString();

#if !defined(__EMSCRIPTEN__)
        locking_ptr<std::string> locked_message(message_, message_mutex_);
        *locked_message = message;

        pthread_create(&command_thread_, NULL, &CallRunCommand, this);
#else
        PostMessageNoLocks(HandleMessageNoLocks(message));
#endif
    }

private:
    project_manager manager;
    osoasso_instance instance;

#if !defined(__EMSCRIPTEN__)
    pthread_t command_thread_;
    pthread_mutex_t message_mutex_;
#endif
    volatile std::string message_;

    std::string HandleMessageNoLocks(const std::string& message)
    {
        return instance.handle_message(message);
    }

#if !defined(__EMSCRIPTEN__)
    void RunCommand()
    {
        {
            locking_ptr<std::string> locked_message(message_, message_mutex_);
            *locked_message = HandleMessageNoLocks(*locked_message);
        }

        pp::Core* core = pp::Module::Get()->core();
        core->CallOnMainThread(0, pp::CompletionCallback(PostMessageCallback, this));
    }

    static void* CallRunCommand(void* This)
    {
        static_cast<OsoassoInstance*>(This)->RunCommand();
        return NULL;
    }
#endif

    void PostMessageNoLocks(const std::string& message)
    {
        osoasso::string_splitter splitter(message, post_message_max_string_length_);
        for (int i = 0; i < splitter.number_of_parts(); ++i)
        {
            std::stringstream part_indicator;
            part_indicator << i + 1 << "," << splitter.number_of_parts() << "," << splitter.part(i);
            PostMessage(pp::Var(part_indicator.str()));
        }
    }

#if !defined(__EMSCRIPTEN__)
    static void PostMessageCallback(void* This, int32_t /*result*/)
    {
        OsoassoInstance* instance = static_cast<OsoassoInstance*>(This);

        locking_ptr<std::string> locked_message(instance->message_, instance->message_mutex_);
        instance->PostMessageNoLocks(*locked_message);
    }
#endif
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

