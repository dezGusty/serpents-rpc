#include "processfactory.h"

namespace serpents{
  namespace launcher{
      std::shared_ptr<Process<int>> ProcessFactory::ExecuteProcessAndWait(const std::string& process_to_execute, 
                                                                          int maximum_timeout_in_millis,
                                                                          Type type,
                                                                          std::string resourceType)
      {
        return std::make_shared<Process<int>>(process_to_execute, maximum_timeout_in_millis,
          [process_to_execute, maximum_timeout_in_millis](){
          return guslib::procrun::ExecuteProcessAndWait(process_to_execute, maximum_timeout_in_millis);
        }, type, resourceType);
      }

      std::shared_ptr<Process<std::string>> ProcessFactory::ExecuteProcessWithOutputCaptureAndWait(const std::string& process_to_execute,
                                                                                                    bool process_visible,
                                                                                                    bool retrieve_output,
                                                                                                    int maximum_timeout_in_millis,
                                                                                                    int& output_code,
                                                                                                    Type type,
                                                                                                    std::string resourceType)
      {
        return std::make_shared<Process<std::string>>(process_to_execute, maximum_timeout_in_millis,
          [process_to_execute, process_visible, retrieve_output, maximum_timeout_in_millis, &output_code](){
          return guslib::procrun::ExecuteProcessWithOutputCaptureAndWait(process_to_execute, process_visible, retrieve_output, maximum_timeout_in_millis, output_code);
        }, type, resourceType);
      }

      std::shared_ptr<Process<void>> ProcessFactory::WaitForProcessTerminationByHandle(HANDLE process_handle,
                                                                                       int timeout_in_millis,
                                                                                       Type type, 
                                                                                       std::string resourceType)
      {
        return std::make_shared <Process<void>>(process_handle, timeout_in_millis, [process_handle, timeout_in_millis]()
        {
          return guslib::procrun::WaitForProcessTerminationByHandle(process_handle, timeout_in_millis);
        }, type, resourceType);
      }

      std::shared_ptr<Process<std::string>> ProcessFactory::ReadPipeContent(HANDLE process_handle, 
                                                                            bool keep_standard_output,
                                                                            Type type,
                                                                            std::string resourceType)
      {
        return std::make_shared<Process<std::string>>(process_handle, keep_standard_output,
          [process_handle, keep_standard_output](){
          return guslib::procrun::ReadPipeContent(process_handle, keep_standard_output);
        }, type, resourceType = "");
      }

  }
}