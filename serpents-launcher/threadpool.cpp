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
      std::chrono::milliseconds sleepDuration(1); // this works but the problem is still there
      std::this_thread::sleep_for(sleepDuration);
      std::unique_lock<std::mutex> ul(Impl_->mutex_);
     
      while (!Impl_->exit_ || (Impl_->finish_work_ && !Impl_->taskQue_.empty())){
        
        if (!Impl_->taskQue_.empty()){
          
          auto task(std::move(Impl_->taskQue_.front()));
          Impl_->taskQue_.pop_front();
          ul.unlock();
          task->exec();
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


  }
}