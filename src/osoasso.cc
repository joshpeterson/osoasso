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

/// These are the method names as JavaScript sees them.  Add any methods for
/// your class here.
namespace osoasso{

const char* const inputMethodId = "input";
const char* const getMatrixMethodId = "getMatrix";
const char* const getLastCommitMethodId = "getLastCommit";

static const char messageArgumentSeparator = ':';

std::string inputPlaceHolder(const std::string& action)
{
    return "bar";
}

double getMatrixPlaceholder(const std::string name)
{
    return 2.72;
}

std::string getLastCommitPlaceholder()
{
    return "foo";
}

pp::Var MarshallInput(const std::string& action)
{
    return pp::Var(inputPlaceHolder(action));
}

pp::Var MarshallGetMatrix(const std::string name)
{
    return pp::Var(getMatrixPlaceholder(name));
}

pp::Var MarshallGetLastCommit()
{
    return pp::Var(getLastCommitPlaceholder());
}

/// The Instance class.  One of these exists for each instance of your NaCl
/// module on the web page.  The browser will ask the Module object to create
/// a new Instance for each occurrence of the <embed> tag that has these
/// attributes:
/// <pre>
///     type="application/x-nacl"
///     nacl="hello_world.nmf"
/// </pre>
class OsoassoInstance : public pp::Instance {
 public:
  explicit OsoassoInstance(PP_Instance instance) : pp::Instance(instance) {}
  virtual ~OsoassoInstance() {}

  /// Called by the browser to handle the postMessage() call in Javascript.
  /// Detects which method is being called from the message contents, and
  /// calls the appropriate function.  Posts the result back to the browser
  /// asynchronously.
  /// @param[in] var_message The message posted by the browser.  The possible
  ///     messages are 'fortyTwo' and 'reverseText:Hello World'.  Note that
  ///     the 'reverseText' form contains the string to reverse following a ':'
  ///     separator.
  virtual void HandleMessage(const pp::Var& var_message);
};

void OsoassoInstance::HandleMessage(const pp::Var& var_message) {
  if (!var_message.is_string()) {
    return;
  }
  std::string message = var_message.AsString();
  pp::Var return_var;
  if (message == getLastCommitMethodId)
  {
    return_var = MarshallGetLastCommit();
  }
  else if (message.find(inputMethodId) == 0)
  {
    // The argument to input is everything after the first ':'.
    size_t sep_pos = message.find_first_of(messageArgumentSeparator);
    if (sep_pos != std::string::npos) {
      std::string string_arg = message.substr(sep_pos + 1);
      return_var = MarshallInput(string_arg);
    }
  }
  else if (message.find(getMatrixMethodId) == 0)
  {
    // The argument to get_matrix is everything after the first ':'.
    size_t sep_pos = message.find_first_of(messageArgumentSeparator);
    if (sep_pos != std::string::npos) {
      std::string string_arg = message.substr(sep_pos + 1);
      return_var = MarshallGetMatrix(string_arg);
    }
  }
  // Post the return result back to the browser.  Note that HandleMessage() is
  // always called on the main thread, so it's OK to post the return message
  // directly from here.  The return post is asynhronous: PostMessage returns
  // immediately.
  PostMessage(return_var);
}

/// The Module class.  The browser calls the CreateInstance() method to create
/// an instance of your NaCl module on the web page.  The browser creates a new
/// instance for each <embed> tag with
/// <code>type="application/x-nacl"</code>.
class OsoassoModule : public pp::Module {
 public:
  OsoassoModule() : pp::Module() {}
  virtual ~OsoassoModule() {}

  /// Create and return a HelloWorldInstance object.
  /// @param[in] instance a handle to a plug-in instance.
  /// @return a newly created HelloWorldInstance.
  /// @note The browser is responsible for calling @a delete when done.
  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new OsoassoInstance(instance);
  }
};
}  // namespace osoasso


namespace pp {
/// Factory function called by the browser when the module is first loaded.
/// The browser keeps a singleton of this module.  It calls the
/// CreateInstance() method on the object you return to make instances.  There
/// is one instance per <embed> tag on the page.  This is the main binding
/// point for your NaCl module with the browser.
/// @return new HelloWorldModule.
/// @note The browser is responsible for deleting returned @a Module.
Module* CreateModule() {
  return new osoasso::OsoassoModule();
}
}  // namespace pp

