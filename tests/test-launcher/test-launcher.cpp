#include "serpents-launcher\threadpool.h"
#include "guslib\system\processrunner.h"
#include <iostream>
#include <chrono>

int main(){
  
  using namespace serpents::launcher;
  serpents::launcher::TaskPool tp(3);
    int n = 20;
      std::future<std::string> f1 = tp.addProcTask<std::string>(
        ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Program Files\\Apache Tomcat 8.0\\bin\\Tomcat8.exe", true, false, 5000, n, Type::BlockAll)
        );
      std::future<std::string> f2 = tp.addProcTask<std::string>(ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Users\\vlad.petrescu\\Documents\\GitHub\\serpents-rpc\\build\\Debug\\testserver.exe", true, false, -1, n, Type::NonBlocking));
      std::future<std::string> f3 = tp.addProcTask<std::string>(ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Users\\vlad.petrescu\\Documents\\GitHub\\serpents-rpc\\build\\Debug\\test-ssl-client.exe", true, false, 5000, n, Type::Blocking));
      std::future<std::string> f4 = tp.addProcTask<std::string>(ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("notepad.exe", true, false, 4000, n, Type::Blocking));
   

    std::cout << "f1 returned " << f1.get() << std::endl;
    std::cout << "f2 returned " << f2.get() << std::endl;
    std::cout << "f3 returned " << f3.get() << std::endl;
    std::cout << "f4 returned " << f4.get() << std::endl;

    tp.waitForCompletion();
 

    

}
