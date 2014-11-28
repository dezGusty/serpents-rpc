#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "serpents-ssl\server/server.hpp"
#include "serpents-ssl\server\serverfunctionrepository.h"
#include "serpents-ssl\log\log.h"
#include "serpents-rpc\serpents\rpc\parameters\retValue.h"
#include "serpents\rpc\server\implservermethod.h"
#include "serpents\rpc\server\method.hpp"
//#define PUGIXML_HEADER_ONLY
using namespace serpents::ssl;

class SampleMethod : public serpents::Method{
public:
  SampleMethod(std::string& name, std::string& help, std::string& signature) {
    setName(name);
    setHelp(help);
    setSignature(signature);

  }
  SampleMethod(){}
  ~SampleMethod(){}
  void execute(serpents::ParameterContainer* pc, RetValue* ret) override{
    //result->add(pc->getInt(0) + pc->getInt(1));
    ret->setValue(pc->getInt(0));
  }
};

int main(){

  try{
    START_LOGGING("type", "log.txt");
    boost::asio::io_service io_service;
    size_t numThreads = 3;

    server s("localhost", io_service, 8080, numThreads);


    std::shared_ptr<serpents::Method> s_method(new SampleMethod);
      s_method->setName(std::string("echo"));
      s.getfunctionRepo().addServerMethod(s_method);
    s.run();
    
  }
  catch (std::exception& e){
    std::cerr << e.what()<<std::endl;
  }
}