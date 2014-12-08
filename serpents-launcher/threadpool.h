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
    std::future<RETVAL> addTask(std::function<RETVAL()>&& function);

    template<typename RETVAL>
    std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);

    template<>
    std::future<void> addTask(std::function<void()>&& function);
   
  private:
    void doWork();
    void joinAll();
    void operator=(const TaskPool&) = delete;
    TaskPool(const TaskPool&) = delete;
  };

  class TaskPool::Impl{
    friend TaskPool;
    std::deque<std::function<void()>> taskQue_;
    std::mutex mutex_;
    std::condition_variable signal_;
    std::atomic<bool> exit_{ false };
    std::atomic<bool> finish_work_{ true };
    std::vector<std::thread> threads_;
  };
  template<typename RETVAL>
  std::future<RETVAL> TaskPool::addTask(std::function<RETVAL()>&& function){
    if (Impl_->exit_){
      throw std::runtime_error("Tried to add task while stopping");
    }

    // Workaround for lack of lambda move capture
    typedef std::pair<std::promise<RETVAL>, std::function<RETVAL()>> pair_t;
    std::shared_ptr<pair_t> data = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));

    std::future<RETVAL> future = data->first.get_future();

    {
      std::lock_guard<std::mutex> lg(Impl_->mutex_);
      Impl_->taskQue_.emplace_back([data](){
        try{
          data->first.set_value(data->second());
        }
        catch (...){
          data->first.set_exception(std::current_exception());
        }
      });
    }
    Impl_->signal_.notify_one();
    return std::move(future);
  }

  template<>
  std::future<void> TaskPool::addTask(std::function<void()>&& function){
    if (Impl_->exit_){
      throw std::runtime_error("");
    }
    // Workaround for lack of lambda move capture
    typedef std::pair<std::promise<void>, std::function<void()>> pair_t;
    std::shared_ptr<pair_t> data = std::make_shared<pair_t>(std::promise<void>(), std::move(function));

    std::future<void> future = data->first.get_future();
  
    {
      std::lock_guard<std::mutex> lg(Impl_->mutex_);
      Impl_->taskQue_.emplace_back([data](){
        try{
          data->second();
          data->first.set_value();
        }
        catch (...){
          data->first.set_exception(std::current_exception());
        }
      });
    }
    Impl_->signal_.notify_one();

    return std::move(future);
  }

  template<typename RETVAL>
  std::future<RETVAL> TaskPool::addProcTask(std::shared_ptr<Process<RETVAL>> proc){
    std::cout << "shit works " << std::endl;
    std::future<RETVAL> future = proc->data_->first.get_future();
    proc->data_->first.set_value(proc->data_->second());
    return future;
  }

  }
}


#endif  //  LAUNCHER_TASK_POOL_H_