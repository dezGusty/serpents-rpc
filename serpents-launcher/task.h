#ifndef LAUNCHER_TASK_H_
#define LAUNCHER_TASK_H_

#include "task.h"
#include <functional>
#include <memory>
#include <mutex>

#include "processutil.h"
#include "launcher_build_opts.h"

namespace serpents{
  namespace launcher{
   
    class LAUNCHER_EXPORT_SYMBOL Task {
    public:
     virtual void cleanUp() =0;
     virtual void exec()=0;
    };

    class LAUNCHER_EXPORT_SYMBOL NonBlockingTask : public Task{
      class Impl;
      Impl* Impl_;
    public:
      NonBlockingTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func);
      ~NonBlockingTask();
      virtual void cleanUp() override;
      virtual void exec() override;
    };

    class LAUNCHER_EXPORT_SYMBOL BlockingTask : public Task{
      class Impl;
      Impl* Impl_;
    public:
      BlockingTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func);
      ~BlockingTask();
      virtual void cleanUp() override;
      virtual void exec() override;
    };
  }
}

#endif  //  LAUNCHER_TASK_H_