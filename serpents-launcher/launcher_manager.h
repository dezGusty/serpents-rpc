#include "guslib\system\processrunner.h"
#include "guslib\common\singleton.hpp"
#include "launcher_build_opts.h"
#include <string>
/*
namespace serpents{
	namespace launcher{
      class LAUNCHER_EXPORT_SYMBOL Process
      {
      public:
        Process(const Process&) = delete;
        Process();
        ~Process();
      private:
        class Impl;
        Impl* Impl_;
       
      };

      class LAUNCHER_EXPORT_SYMBOL LaunchManagerUtil
      {
      public:
        enum action{
          ExecuteProcessAndWait, ExecuteProcessWithOutputCaptureAndWait, GetLocalHostName,
          ExecuteProcessWithOutputCaptureAndWaitWindows, WaitForProcessTerminationByHandle, GetProcessReturnCode,
          ReadPipeContent, ExecuteProcessWithOutputCaptureAndWaitLinux, ExecuteProcessAndWaitLinux, GetLocalHostNameLinux
        };
        LaunchManagerUtil(const LaunchManagerUtil&) = delete;
        LaunchManagerUtil();
        ~LaunchManagerUtil();


       int ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis);

       std::string ExecuteProcessWithOutputCaptureAndWait(
         const std::string& process_to_execute,
         bool process_visible,
         bool retrieve_output,
         int maximum_timeout_in_millis,
         int& output_code);

       std::string GetLocalHostName();
      private:
        class Impl;
        Impl* Impl_;
             
      
      };
      
      typedef guslib::Singleton<LaunchManagerUtil> LaunchManager;
      LAUNCHER_EXPIMP_TEMPLATE template class LAUNCHER_EXPORT_SYMBOL guslib::Singleton <LaunchManagerUtil>;
	}
}
*/