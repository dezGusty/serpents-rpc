#include "task.h"

namespace serpents{
  namespace launcher{
    class NonBlockingTask::Impl{
      friend NonBlockingTask;
      Impl();
      ~Impl();
      HANDLE Handle_;
      ProcessUtil* procUtil;
      std::string process_to_execute_;
      int timeout_;
      std::unique_ptr<std::function<void()>> function_;
    };
    NonBlockingTask::Impl::Impl(){
      procUtil = new ProcessUtil;
    }
    NonBlockingTask::Impl::~Impl(){
      delete procUtil;
    }
    NonBlockingTask::NonBlockingTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func)
    {
      Impl_ = new Impl;
      Impl_->process_to_execute_ = process_to_execute;
      Impl_->timeout_ = timeout;
      Impl_->Handle_ = Handle;
      Impl_->procUtil = new ProcessUtil;
      Impl_->function_ = std::make_unique<std::function<void()>>(std::move(func));
    }

    void NonBlockingTask::cleanUp(){
      if (Impl_->Handle_ != nullptr){
        ProcessUtil::closeProcessByHandle(Impl_->Handle_);
      }
      else{
        ProcessUtil::closeProcessByName(Impl_->process_to_execute_);
      }
    }
    void NonBlockingTask::exec(){
      auto func = *Impl_->function_.get();
      func();
      cleanUp();
    }
    NonBlockingTask::~NonBlockingTask(){
      delete Impl_;
    }
  }
}