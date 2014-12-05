#ifndef PROCESS_FACTORY_H_
#define PROCESS_FACTORY_H_
#include <future>
#include <string>
namespace serpents{
  namespace laucher{
    class Process{
      std::future<int> ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis);
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
    };
  }
}

#endif //  PROCESS_FACTORY_H_