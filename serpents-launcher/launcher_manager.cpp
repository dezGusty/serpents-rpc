#include "launcher_manager.h"

#include "guslib\system\systemmutex.h"
#include <memory>
#include <queue>
/*
namespace serpents
{
  namespace launcher
  {
    struct ProcessStruct{
      ProcessStruct(Process& proc, LaunchManagerUtil::action& action);
      ProcessStruct(const ProcessStruct&) = delete;
      Process proc;
      LaunchManagerUtil::action action;
    };
    ProcessStruct::ProcessStruct(Process& proc, LaunchManagerUtil::action& action)
    {
      this->proc = proc;
      this->action = action;
    }
    class LaunchManagerUtil::Impl
    {
      friend LaunchManagerUtil;
      std::queue<std::shared_ptr<ProcessStruct>> processList;
      guslib::mutex::MutexHandle mutexHandle;
    };

    LaunchManagerUtil::LaunchManagerUtil()
    {
      Impl_ = new Impl;
      bool alreadyExists;
      Impl_->mutexHandle = guslib::mutex::CreateNamedMutex("launchManagerMutex", alreadyExists,true);
    }
    LaunchManagerUtil::~LaunchManagerUtil()
    {
      guslib::mutex::DestroyMutex(Impl_->mutexHandle);
      delete Impl_;
    }
    int LaunchManagerUtil::ExecuteProcessAndWait(const std::string& process_to_execute, int maximum_timeout_in_millis){
      guslib::mutex::LockMutex(Impl_->mutexHandle);
      int retvalue = guslib::procrun::ExecuteProcessAndWait(process_to_execute,maximum_timeout_in_millis);
      guslib::mutex::UnlockMutex(Impl_->mutexHandle);
      return retvalue;
    }

    std::string LaunchManagerUtil::ExecuteProcessWithOutputCaptureAndWait(
      const std::string& process_to_execute,
      bool process_visible,
      bool retrieve_output,
      int maximum_timeout_in_millis,
      int& output_code)
    {
      guslib::mutex::LockMutex(Impl_->mutexHandle);
      std::string retValue = ExecuteProcessWithOutputCaptureAndWait(process_to_execute, process_visible, retrieve_output,
        maximum_timeout_in_millis, output_code);
      guslib::mutex::UnlockMutex(Impl_->mutexHandle);
      return retValue;
    }

    std::string LaunchManagerUtil::GetLocalHostName(){
      guslib::mutex::LockMutex(Impl_->mutexHandle);
      std::string retValue =guslib::procrun::GetLocalHostName();
      guslib::mutex::UnlockMutex(Impl_->mutexHandle);
      return retValue;
    }
    class Process::Impl
    {
      friend Process;
      const std::string& process_to_execute;
      bool process_visible;
      bool retrieve_output;
      int maximum_timeout_in_millis;
      int& output_code;
      HANDLE process_handle;
    };
    Process::Process()
    {
      Impl_ = new Impl;
    }
    Process::~Process()
    {
      delete Impl_;
     }

  }
}
*/