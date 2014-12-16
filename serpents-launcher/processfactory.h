#ifndef PROCESS_FACTORY_H_
#define PROCESS_FACTORY_H_
#include <future>
#include <string>
#include "guslib\system\processrunner.h"
#include "launcher_build_opts.h"
namespace serpents{
  namespace launcher{
    enum Type {Blocking, NonBlocking, BlockAll};
    template<typename RETVAL>
    class Process{
    public:
      Type type_;
      std::string process_to_execute_;
      int maximum_timeout_in_millis_;
      HANDLE Handle_;
      typedef std::pair<std::promise<RETVAL>, std::function<RETVAL()>> pair_t;
      std::shared_ptr<pair_t> data_;
      std::string resourceType_;
      Process(const std::string& process_to_execute, int maximum_timeout_in_millis, std::function<RETVAL()>&& function, Type type = Type::NonBlocking, std::string& resourceType = "")
      {
        process_to_execute_ =process_to_execute;
        maximum_timeout_in_millis_ =maximum_timeout_in_millis;
        Handle_ =nullptr;
        resourceType_= resourceType;
        type_=type;
        data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
      }
      Process(HANDLE Handle, int maximum_timeout_in_millis, std::function<RETVAL()>&& function, Type type = Type::NonBlocking, std::string& resourceType = "")
      {
        process_to_execute_="";
        maximum_timeout_in_millis_=maximum_timeout_in_millis;
        resourceType_ = resourceType;
        Handle_ = Handle;
        type_ = type;
        data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
      }
      Process(HANDLE process_handle,std::function<RETVAL()>&& function, Type type = Type::NonBlocking, std::string& resourceType = "")
      {
        process_to_execute_="";
        maximum_timeout_in_millis_ = -1;
        Handle_ = Handle;
        resourceType_ = resourceType;
        type_ = type;
      }
    };
    class LAUNCHER_EXPORT_SYMBOL ProcessFactory{
    public:
      static std::shared_ptr<Process<int>> ExecuteProcessAndWait(const std::string& process_to_execute, 
                                                                 int maximum_timeout_in_millis,
                                                                 Type type = Type::NonBlocking,
                                                                 std::string resourceType = "");
      
      static std::shared_ptr<Process<std::string>> ExecuteProcessWithOutputCaptureAndWait(const std::string& process_to_execute,
                                                                                          bool process_visible,
                                                                                          bool retrieve_output,
                                                                                          int maximum_timeout_in_millis,
                                                                                          int& output_code,
                                                                                          Type type = Type::NonBlocking,
                                                                                          std::string resourceType = "");
      
      static std::shared_ptr<Process<void>> WaitForProcessTerminationByHandle(HANDLE process_handle, 
                                                                             int timeout_in_millis,
                                                                             Type type = Type::NonBlocking, 
                                                                             std::string resourceType = "");
      
      static std::shared_ptr<Process<std::string>> ReadPipeContent(HANDLE process_handle, 
                                                                   bool keep_standard_output, 
                                                                   Type type = Type::NonBlocking, 
                                                                   std::string resourceType = "");
    };
  }
}

#endif //  PROCESS_FACTORY_H_