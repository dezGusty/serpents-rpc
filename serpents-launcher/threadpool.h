#ifndef LAUNCHER_TASK_POOL_H_
#define LAUNCHER_TASK_POOL_H_

// based off the immpl found @ http://codereview.stackexchange.com/questions/60363/thread-pool-worker-implementation

#include "launcher_build_opts.h"
#include <iostream>
#include <functional>
#include <future>
#include <deque>
#include <thread>

#include "processfactory.h"

namespace serpents{
  namespace launcher{
    
    class Task {
    public:
      std::string process_to_execute_;
      int timeout_;
      HANDLE Handle_;
      std::unique_ptr<std::function<void()>> function_;
    public:
      Task(std::string& process_to_execute, int timeout,HANDLE Handle, std::function<void()>&& func)
        :process_to_execute_(process_to_execute),
        timeout_(timeout),
        Handle_(Handle)
      {
        function_ = std::make_unique<std::function<void()>>(std::move(func));
      }
      void exec(){
        std::cout << "Process " << process_to_execute_ << " timeout " << timeout_ << " Handle " << Handle_ << std::endl;
        auto func = *function_.get();
        func();
      }
    };
    

  class LAUNCHER_EXPORT_SYMBOL TaskPool{
  public:
    class Impl;
    Impl* Impl_;
    explicit TaskPool(int numWorkers = -1);
    ~TaskPool();
    void abort();
    void stop();  
    void waitForCompletion();
 
    template<typename RETVAL>
    std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);
   
  private:
    void doWork();
    void joinAll();
    void operator=(const TaskPool&) = delete;
    TaskPool(const TaskPool&) = delete;
  };

  class TaskPool::Impl{
    friend TaskPool;
    std::deque<std::shared_ptr<Task>> taskQue_;
    std::mutex mutex_;
    std::condition_variable signal_;
    std::atomic<bool> exit_{ false };
    std::atomic<bool> finish_work_{ true };
    std::vector<std::thread> threads_;
  };
 
  template<typename RETVAL>
  std::future<RETVAL> TaskPool::addProcTask(std::shared_ptr<Process<RETVAL>> proc){
    std::future<RETVAL> future = proc->data_->first.get_future();

    Impl_->taskQue_.emplace_back(std::make_shared<Task>(
      proc->process_to_execute_,
      proc->maximum_timeout_in_millis_,
      proc->Handle_,
      [proc](){
      try{
        proc->data_->first.set_value(proc->data_->second());

      }
      catch (...){
        proc->data_->first.set_exception(std::current_exception());
      }
    }

    ));

    return std::move(future);
  }
  
  template<>
  std::future<void> TaskPool::addProcTask(std::shared_ptr<Process<void>> proc){
    std::future<void> future = proc->data_->first.get_future();
    
    Impl_->taskQue_.emplace_back(std::make_shared<Task>(
      proc->process_to_execute_,
      proc->maximum_timeout_in_millis_,
      proc->Handle_,
      [proc](){
      try{
        proc->data_->first.set_value();
        proc->data_->second();
      }
      catch (...){
        proc->data_->first.set_exception(std::current_exception());
      }
    } 
   
    ));
   
    return std::move(future);
  }

  }

}


#endif  //  LAUNCHER_TASK_POOL_H_