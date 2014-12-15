#include "task.h"
#include <atomic>
#include <thread>
namespace serpents{
  namespace launcher{
    std::mutex block;
    std::mutex blockAll;
    std::atomic<bool> isBlocked =false;

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
      while (isBlocked)
      {
        std::this_thread::yield();
      }
      auto func = *Impl_->function_.get();
      func();
      cleanUp();
    }
    NonBlockingTask::~NonBlockingTask(){
      delete Impl_;
    }


    class BlockingTask::Impl{
      friend BlockingTask;
      Impl();
      ~Impl();
      HANDLE Handle_;
      ProcessUtil* procUtil;
      std::string process_to_execute_;
      int timeout_;
      std::unique_ptr<std::function<void()>> function_;
    };
    BlockingTask::Impl::Impl(){
      procUtil = new ProcessUtil;
    }
    BlockingTask::Impl::~Impl(){
      delete procUtil;
    }
    BlockingTask::BlockingTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func)
    {
      Impl_ = new Impl;
      Impl_->process_to_execute_ = process_to_execute;
      Impl_->timeout_ = timeout;
      Impl_->Handle_ = Handle;
      Impl_->procUtil = new ProcessUtil;
      Impl_->function_ = std::make_unique<std::function<void()>>(std::move(func));
    }

    void BlockingTask::cleanUp(){
      if (Impl_->Handle_ != nullptr){
        ProcessUtil::closeProcessByHandle(Impl_->Handle_);
      }
      else{
        ProcessUtil::closeProcessByName(Impl_->process_to_execute_);
      }
    }
    void BlockingTask::exec(){
      {
        while (isBlocked)
        {
          std::this_thread::yield();
        }
        std::lock_guard<std::mutex> lock(block);
        auto func = *Impl_->function_.get();
        func();
      }
      cleanUp();
    }
    BlockingTask::~BlockingTask(){
      delete Impl_;
    }
    
    // block all task
    class BlockingAllTask::Impl{
      friend BlockingAllTask;
      Impl();
      ~Impl();
      HANDLE Handle_;
      ProcessUtil* procUtil;
      std::string process_to_execute_;
      int timeout_;
      std::unique_ptr<std::function<void()>> function_;
    };
    BlockingAllTask::Impl::Impl(){
      procUtil = new ProcessUtil;
    }
    BlockingAllTask::Impl::~Impl(){
      delete procUtil;
    }
    BlockingAllTask::BlockingAllTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func)
    {
      Impl_ = new Impl;
      Impl_->process_to_execute_ = process_to_execute;
      Impl_->timeout_ = timeout;
      Impl_->Handle_ = Handle;
      Impl_->procUtil = new ProcessUtil;
      Impl_->function_ = std::make_unique<std::function<void()>>(std::move(func));
    }

    void BlockingAllTask::cleanUp(){
      if (Impl_->Handle_ != nullptr){
        ProcessUtil::closeProcessByHandle(Impl_->Handle_);
      }
      else{
        ProcessUtil::closeProcessByName(Impl_->process_to_execute_);
      }
    }
    void BlockingAllTask::exec(){
      {
        std::lock_guard<std::mutex> lockAll(blockAll); 
        isBlocked = true;
        auto func = *Impl_->function_.get();
        std::thread t([func](){ func();  });
        t.join();
      }
      isBlocked = false;
      cleanUp();
    }
    BlockingAllTask::~BlockingAllTask(){
      delete Impl_;
    }
  }
}