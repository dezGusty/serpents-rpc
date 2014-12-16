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
     virtual int getTimeout() = 0;
     virtual void cleanUp() =0;
     virtual void exec()=0;
     virtual ~Task() {};
    };

    class LAUNCHER_EXPORT_SYMBOL NonBlockingTask : public Task{
      class Impl;
      Impl* Impl_;
    public:
      NonBlockingTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func);
      ~NonBlockingTask();
      virtual void cleanUp() override;
      virtual void exec() override;
      virtual int getTimeout() override;
    };

    class LAUNCHER_EXPORT_SYMBOL BlockingTask : public Task{
      class Impl;
      Impl* Impl_;
    public:
      BlockingTask(const std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func, const std::string& resourceType = "");
      ~BlockingTask();
      virtual void cleanUp() override;
      virtual void exec() override;
      virtual int getTimeout() override;
    };
    class LAUNCHER_EXPORT_SYMBOL BlockingAllTask : public Task{
      class Impl;
      Impl* Impl_;
    public:
      BlockingAllTask(std::string& process_to_execute, int timeout, HANDLE Handle, std::function<void()>&& func);
      ~BlockingAllTask();
      virtual void cleanUp() override;
      virtual void exec() override;
      virtual int getTimeout() override;
    };
  }
}

#endif  //  LAUNCHER_TASK_H_