#ifndef LAUNHER_THREAD_POOL_H_
#define LAUNHER_THREAD_POOL_H_

//  based off thread pool example @ http://codereview.stackexchange.com/questions/60363/thread-pool-worker-implementation

#include <future>
#include <functional>
#include <deque>
#include <atomic>
#include <functional>
#include <vector>

namespace serpents{
  namespace launcher{
   
    class ThreadPool{
    public:
      enum action {BLOCKING, NONBLOCKING, PRIORITY};
      explicit ThreadPool(int numThreads =1){
        if (numThreads < 1)
          throw std::runtime_error("TreadPool can't have less than one thread");
        while (numThreads>0){
          workQue_.emplace_back(&ThreadPool::doWork, this);
        }
      }
      virtual ~ThreadPool(){}
      ThreadPool(const ThreadPool& that) = delete;
      ThreadPool(ThreadPool&& that){}
      ThreadPool& operator=(const ThreadPool& that) = delete;
      
      //non-blocking 
      template<typename RetVal>
      std::future<RetVal> addTask(std::function<RetVal()>&& function){
        if (exit_){
          throw std::runtime_error("Caught work submission to work queue that is desisting.");
        }

        // Workaround for lack of lambda move capture
        typedef std::pair<std::promise<RETVAL>, std::function<RETVAL()>> pair_t;
        std::shared_ptr<pair_t> data = std::make_shared<pair_t>(std::promise<RETVAL>(), std::move(function));

        std::future<RETVAL> future = data->first.get_future();

        {
          std::lock_guard<std::mutex> lg(addTaskMutex_);
          workQue_.emplace_back([data](){
            try{
              data->first.set_value(data->second());
            }
            catch (...){
              data->first.set_exception(std::current_exception());
            }
          });
        }
        m_signal.notify_one();
        return std::move(future);
      }

  
    private:

      void doWork(){
        std::unique_lock<std::mutex> ul(blockingMutex);
        while (!exit || (finish_work_ && !workQue_.empty())){
          if (!workQue_.empty()){
            std::function<void()> work(std::move(workQue_.front()));
            workQue_.pop_front();
            ul.unlock();
            work();
            ul.lock();
          }
          else{
            signal_.wait(ul);
          }
        }
      }
      void joinAll(){
        for (auto& thread : workThreads_){
          thread.join();
        }
        workThreads_.clear();
      }

      std::vector<std::thread> workThreads_;
      std::deque<std::function<void()>> workQue_;
      std::atomic<bool> blockAll_{ false };
      std::atomic<bool> exit_{ false };
      std::mutex addTaskMutex_;
      std::mutex blockingMutex;
      std::mutex blockAllMutex;
      std::atomic<bool> finish_work_{ true };
      std::condition_variable signal_;
      size_t numThreads;
    };

 

  }
}

#endif //  LAUNHER_THREAD_POOL_H_