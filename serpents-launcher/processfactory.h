#ifndef PROCESS_FACTORY_H_
#define PROCESS_FACTORY_H_
#include <future>
#include <string>
#include "guslib\system\processrunner.h"
namespace serpents{
  namespace launcher{
    enum Type {Blocking, NonBlocking};
    template<typename RETVAL>
    class Process{
    public:
      Type type_;
      std::string process_to_execute_;
      int maximum_timeout_in_millis_;
      HANDLE Handle_;
      typedef std::pair<std::promise<RETVAL>, std::function<RETVAL()>> pair_t;
      std::shared_ptr<pair_t> data_;
      Process(const std::string& process_to_execute, int maximum_timeout_in_millis, std::function<RETVAL()>&& function, Type type = Type::NonBlocking)
        :process_to_execute_(process_to_execute),
         maximum_timeout_in_millis_(maximum_timeout_in_millis),
         Handle_(nullptr),
         type_(type)
      {
        data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
      }
      Process(HANDLE Handle, int maximum_timeout_in_millis, std::function<RETVAL()>&& function, Type type = Type::NonBlocking)
        :process_to_execute_(""),
        maximum_timeout_in_millis_(maximum_timeout_in_millis),
        Handle_(Handle)
      {
        data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
      }
    };
    class ProcessFactory{
    public:
      static std::shared_ptr<Process<int>> ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis, 
                                                                Type type = Type::NonBlocking)
      {
        return std::make_shared<Process<int>>(process_to_execute, maximum_timeout_in_millis, 
          [process_to_execute, maximum_timeout_in_millis](){
              return guslib::procrun::ExecuteProcessAndWait(process_to_execute, maximum_timeout_in_millis);
        }, type);
      }
      
      static std::shared_ptr<Process<std::string>> ExecuteProcessWithOutputCaptureAndWait(const std::string& process_to_execute,
                                                                  bool process_visible,
                                                                  bool retrieve_output,
                                                                  int maximum_timeout_in_millis,
                                                                  int& output_code,
                                                                  Type type = Type::NonBlocking)
      {
        return std::make_shared<Process<std::string>>(process_to_execute, maximum_timeout_in_millis,
          [process_to_execute, process_visible, retrieve_output, maximum_timeout_in_millis, &output_code](){
          return guslib::procrun::ExecuteProcessWithOutputCaptureAndWait(process_to_execute, process_visible, retrieve_output, maximum_timeout_in_millis, output_code);
        },type);
      }
      
      static std::shared_ptr<Process<void>> WaitForProcessTerminationByHandle(HANDLE process_handle, int timeout_in_millis, Type type = Type::NonBlocking)
      {
        return std::make_shared <Process<void>>(process_handle, timeout_in_millis, [process_handle, timeout_in_millis]()
        { 
          return guslib::procrun::WaitForProcessTerminationByHandle(process_handle, timeout_in_millis);
        },type);
      }
      
     
    };
  }
}

#endif //  PROCESS_FACTORY_H_