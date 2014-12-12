#include "serpents-launcher\threadpool.h"
#include "guslib\system\processrunner.h"
#include <iostream>
#include <chrono>

int main(){
  using namespace serpents::launcher;
  serpents::launcher::TaskPool tp(3);
  int n = 20;
    std::future<std::string> f2 = tp.addProcTask<std::string>(
      ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Program Files\\Apache Tomcat 8.0\\bin\\Tomcat8.exe", true, false, -1, n)
      );
    std::future<std::string> f1 = tp.addProcTask<std::string>(ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Users\\vlad.petrescu\\Documents\\GitHub\\serpents-rpc\\build\\Debug\\testserver.exe",true, false, -1,n));
    std::future<std::string> f3 = tp.addProcTask<std::string>(ProcessFactory::ExecuteProcessWithOutputCaptureAndWait("C:\\Users\\vlad.petrescu\\Documents\\GitHub\\serpents-rpc\\build\\Debug\\test-ssl-client.exe", true, false, -1, n));
    std::cout << "f1 returned "<< f1.get();
    std::cout << "f3 returned " << f3.get();
    std::cout << "---f2 returned  " << f2.get() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
