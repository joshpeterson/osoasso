/// @file osoasso.cc
/// This example demonstrates loading, running and scripting a very simple NaCl
/// module.  To load the NaCl module, the browser first looks for the
/// CreateModule() factory method (at the end of this file).  It calls
/// CreateModule() once to load the module code from your .nexe.  After the
/// .nexe code is loaded, CreateModule() is not called again.
///
/// Once the .nexe code is loaded, the browser than calls the CreateInstance()
/// method on the object returned by CreateModule().  It calls CreateInstance()
/// each time it encounters an <embed> tag that references your NaCl module.
///
/// When the browser encounters JavaScript that references your NaCl module, it
/// calls the GetInstanceObject() method on the object returned from
/// CreateInstance().  In this example, the returned object is a subclass of
/// ScriptableObject, which handles the scripting support.

#include <ppapi/cpp/dev/scriptable_object_deprecated.h>
#include <ppapi/cpp/instance.h>
#include <ppapi/cpp/module.h>
#include <ppapi/cpp/var.h>
#include <cstdio>
#include <string>
#include <stdexcept>
#include "../include/osoasso_instance.h"
#include "../include/project_manager.h"

/// These are the method names as JavaScript sees them.  Add any methods for
/// your class here.
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

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
/// <pre>
///     type="application/x-nacl"
///     nacl="hello_world.nmf"
/// </pre>
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

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with
/// <code>type="application/x-nacl"</code>.
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

