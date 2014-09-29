#ifndef PROCESSRUNNER_H_
#define PROCESSRUNNER_H_
#include <windows.h>
#include <string>
#include <sstream>
#include "serpents/rpc/base.h"
#include <vector>
namespace serpents{
  namespace procrun{
    int SERPENTSDLL ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis);
    std::string SERPENTSDLL ExecuteProcessWithOutputCaptureAndWaitWindows(
      const std::string& process_to_execute,
      bool process_visible,
      bool retrieve_output,
      int maximum_timeout_in_millis,
      int& output_code);

    std::string SERPENTSDLL ExecuteProcessWithOutputCaptureAndWait(
      const std::string& process_to_execute,
      bool process_visible,
      bool retrieve_output,
      int maximum_timeout_in_millis,
      int& output_code);

    void SERPENTSDLL  WaitForProcessTerminationByHandle(HANDLE process_handle, int timeout_in_millis);

    int  SERPENTSDLL GetProcessReturnCode(HANDLE process_handle);

    std::string  SERPENTSDLL ReadPipeContent(HANDLE process_handle, bool keep_standard_output);

    std::string  SERPENTSDLL GetLocalHostName();
  }
}

#endif // PROCESSRUNNER_H_