#include "task.h"
#include <atomic>
#include <thread>
#include <set>
#include <map>
namespace serpents{
  namespace launcher{
    std::mutex block;
    std::mutex blockAll;
    std::mutex addResourceTypeMutex;
    std::set<std::string> resourceTypesInUse;
    typedef std::pair <std::string, std::unique_ptr<std::mutex>> pair_t;
    std::map<std::string, std::unique_ptr<std::mutex*>> resourceMap;
    std::atomic<bool> isBlocked =false;

    class NonBlockingTask::Impl{
      friend NonBlockingTask;
      Impl();
      ~Impl();
      HANDLE Handle_;
      ProcessUtil* procUtil;
      std::atomic<bool> cleanedUp = false;
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
      if (Impl_->Handle_ != nullptr && !Impl_->cleanedUp){
        ProcessUtil::closeProcessByHandle(Impl_->Handle_);
      }
      else{
        ProcessUtil::closeProcessByName(Impl_->process_to_execute_);
      }
    }
    int NonBlockingTask::getTimeout(){
      return Impl_->timeout_;
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
      std::string resourceType_;
      int timeout_;
      std::atomic<bool> cleanedUp = false;
      std::unique_ptr<std::function<void()>> function_;
    };
    BlockingTask::Impl::Impl(){
      procUtil = new ProcessUtil;
    }
    BlockingTask::Impl::~Impl(){
      delete procUtil;
    }
    BlockingTask::BlockingTask(const std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func,const std::string& resourceType)
    {
      Impl_ = new Impl;
      Impl_->process_to_execute_ = process_to_execute;
      Impl_->timeout_ = timeout;
      Impl_->Handle_ = Handle;
      Impl_->procUtil = new ProcessUtil;
      Impl_->function_ = std::make_unique<std::function<void()>>(std::move(func));
      Impl_->resourceType_ = resourceType;
    }
    int BlockingTask::getTimeout(){
      return Impl_->timeout_;
    }
    void BlockingTask::cleanUp(){
      if (Impl_->Handle_ != nullptr && !Impl_->cleanedUp){
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
        { 
          std::lock_guard<std::mutex> lock(addResourceTypeMutex);
          if (resourceMap.find(Impl_->resourceType_) == resourceMap.end()){
            if (Impl_->resourceType_.compare("") != 0){
              resourceMap[Impl_->resourceType_] = std::make_unique<std::mutex*>(new std::mutex());
            }
          }
        }
        auto it = resourceMap.find(Impl_->resourceType_);
        if (it != resourceMap.end()){
          try{
            std::lock_guard<std::mutex> l(**it->second);
            auto func = *Impl_->function_.get();
            func();
          }
          catch (...){
            std::lock_guard<std::mutex> lock(addResourceTypeMutex);
            auto it = resourceMap.find(Impl_->resourceType_);
            resourceMap.erase(Impl_->resourceType_);
          }
          {
            std::lock_guard<std::mutex> lock(addResourceTypeMutex);
            if (resourceMap.find(Impl_->resourceType_) != resourceMap.end())
            {
              auto it = resourceMap.find(Impl_->resourceType_);
              resourceMap.erase(Impl_->resourceType_);
            }
          }
        }
        else{
          auto func = *Impl_->function_.get();
          func();
        }
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
      std::atomic<bool> cleanedUp = false;
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
      std::thread timer;
    }
    int BlockingAllTask::getTimeout(){
      return Impl_->timeout_;
    }
    void BlockingAllTask::cleanUp(){
      if (Impl_->Handle_ != nullptr &&  !Impl_->cleanedUp){
        ProcessUtil::closeProcessByHandle(Impl_->Handle_);
      }
      else{
        ProcessUtil::closeProcessByName(Impl_->process_to_execute_);
      }
      Impl_->cleanedUp = true;
    }
    void BlockingAllTask::exec(){
      {
        std::lock_guard<std::mutex> lockAll(blockAll); 
        isBlocked = true;
        
        auto func = *Impl_->function_.get();
        try{
          func();
        }
        catch (...){
          isBlocked = false;
          cleanUp();
        }
      }
      isBlocked = false;
      cleanUp();
    }
    BlockingAllTask::~BlockingAllTask(){
      isBlocked = false;
      delete Impl_;
    }
  }
}