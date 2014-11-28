//serpents libs
#include "serpents/rpc/base.h"
#include "serpents/rpc/server/server.h"
#include "serpents/rpc/log/log.h"
#include "serpents/rpc/parameters/parametercontainer.hpp"


//xmlrpc++ libs
#include <xmlrpc++/XmlRpc.h>

//c++ system libs
#include <sstream> 
#include <mutex>
#include <string>

namespace serpents{

  class  XMLRPC_Method : public XmlRpc::XmlRpcServerMethod{
  public:
    std::mutex mtx;
    Method* method;
    XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s);
    void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);

    void fillParameterContainer(ParameterContainer& pc, XmlRpc::XmlRpcValue& params);
  };


}
