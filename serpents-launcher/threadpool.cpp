#include "threadpool.h"

namespace serpents{
  namespace launcher{

    TaskPool::TaskPool(int numWorkers){
      Impl_ = new Impl;
      if (numWorkers < 1){
        numWorkers = std::thread::hardware_concurrency() + 1;
      }
      while (numWorkers--){
        Impl_->threads_.emplace_back(std::thread(&TaskPool::doWork, this));
      }
    }
    TaskPool:: ~TaskPool(){
      abort();
      delete Impl_;
    }


    void  TaskPool::abort(){
      Impl_->exit_ = true;
      Impl_->finish_work_ = false;
      Impl_->signal_.notify_all();
      joinAll();

      {
        std::lock_guard<std::mutex> lg(Impl_->mutex_);
        Impl_->taskQue_.clear();
      }
    }


    void  TaskPool::stop(){
      Impl_->exit_ = true;
      Impl_->finish_work_ = true;
      Impl_->signal_.notify_all();
      
    }


    void  TaskPool::waitForCompletion(){
      stop();
      joinAll();
      assert(Impl_->taskQue_.empty());
    }
    void TaskPool::doWork(){
      std::unique_lock<std::mutex> ul(Impl_->mutex_);
      while (!Impl_->exit_ || (Impl_->finish_work_ && !Impl_->taskQue_.empty())){
        if (!Impl_->taskQue_.empty()){
          std::function<void()> work(std::move(Impl_->taskQue_.front()));
          Impl_->taskQue_.pop_front();
          ul.unlock();
          work();
          ul.lock();
        }
        else{
          Impl_->signal_.wait(ul);
        }
      }
    }

    void TaskPool::joinAll(){
      for (auto& thread : Impl_->threads_){
        thread.join();
      }
      Impl_->threads_.clear();
    }
    
    
    LAUNCHER_EXPIMP_TEMPLATE  template std::future<int> TaskPool::addTask(std::function<int()>&&);
  }
}