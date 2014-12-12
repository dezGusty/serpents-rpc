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
#include "task.h"

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
    std::future<RETVAL> addProcTask(std::shared_ptr<Process<RETVAL>> proc);
   
  private:
    void doWork();
    void joinAll();
    void operator=(const TaskPool&) = delete;
    TaskPool(const TaskPool&) = delete;
  };

  class TaskPool::Impl{
    friend TaskPool;
    std::deque<std::shared_ptr<Task*>> taskQue_;
    std::mutex mutex_;
    std::condition_variable signal_;
    std::atomic<bool> exit_{ false };
    std::atomic<bool> finish_work_{ true };
    std::vector<std::thread> threads_;
  };
 
#include "addProdTask.inl"
  }

}


#endif  //  LAUNCHER_TASK_POOL_H_