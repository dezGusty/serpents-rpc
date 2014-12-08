#ifndef PROCESS_FACTORY_H_
#define PROCESS_FACTORY_H_
#include <future>
#include <string>
#include "guslib\system\processrunner.h"
namespace serpents{
  namespace launcher{
    template<typename RETVAL>
    class Process{
    public:
      std::string process_to_execute_;
      int maximum_timeout_in_millis_;
      HANDLE Handle_;
      typedef std::pair<std::promise<RETVAL>, std::function<RETVAL()>> pair_t;
      std::shared_ptr<pair_t> data_;
      Process(const std::string& process_to_execute, int maximum_timeout_in_millis, std::function<RETVAL()>&& function) 
        :process_to_execute_(process_to_execute),
         maximum_timeout_in_millis_(maximum_timeout_in_millis)
      {
        data_ = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));
      }
    };
    class ProcessFactory{
    public:
      static std::shared_ptr<Process<int>> ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis){
        return std::make_shared<Process<int>>(process_to_execute, maximum_timeout_in_millis, 
          [process_to_execute, maximum_timeout_in_millis](){
              return guslib::procrun::ExecuteProcessAndWait(process_to_execute, maximum_timeout_in_millis);
        });
      }
      /*
      std::future<std::string> ExecuteProcessWithOutputCaptureAndWait(const std::string& process_to_execute,
                                                                      bool process_visible,
                                                                      bool retrieve_output,
                                                                      int maximum_timeout_in_millis,
                                                                      int& output_code);
      std::future<std::string> ExecuteProcessWithOutputCaptureAndWaitWindows(const std::string& process_to_execute,
                                                                bool process_visible,
                                                                bool retrieve_output,
                                                                int maximum_timeout_in_millis,
                                                                int& output_code);
      std::future<void> WaitForProcessTerminationByHandle(HANDLE process_handle, int timeout_in_millis);
      */
    };
  }
}

#endif //  PROCESS_FACTORY_H_