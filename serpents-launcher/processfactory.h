#ifndef PROCESS_FACTORY_H_
#define PROCESS_FACTORY_H_
#include <future>
#include <string>
namespace serpents{
  namespace laucher{
  /*  template<typename >
    class Process{
      std::future<int> ExecuteProcessAndWait();
      std::future<std::string> ExecuteProcessWithOutputCaptureAndWait();
      void WaitForProcessTerminationByHandle();
      void ();
    };
    class ExecuteProcessAndWait : public Process{
      std::future<int> operator()();
      template<typename RETVALUE>
      std::future<RETVALUE> getSomething() {};
      int getTimeoutInMillis() {};
      std::string getName() {};
      HANDLE getHandle() {};
    };
    class ExecuteProcessWithOutputCaptureAndWait{
     
    };
    */
    class WaitForProcessTerminationByHandle{
      HANDLE handle;
      int timeout_in_millis;
      void operator()();

    };

    class ReadPipeContent{

    };
    class GetProcessReturnCode{

    };
    class GetLocalHostName{

    };
  }
}

#endif //  PROCESS_FACTORY_H_