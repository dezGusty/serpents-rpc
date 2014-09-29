
#ifndef IMPLSERVERMETHOD_H_
#define IMPLSERVERMETHOD_H_

//serpents libs
#include "serpents/rpc/base.h"
#include "serpents/rpc/server/server.h"
#include "serpents/rpc/log/log.h"
#include "serpents/rpc/parameters/parametercontainer.h"

//xmlrpc-c libs
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

//xmlrpc++ libs
#include <xmlrpc++/XmlRpc.h>

//c++ system libs
#include <sstream> 
#include <mutex>
#include <string>

#ifdef SERPENTSRPC_EXPORTS
#define IMPLSERVERMETHOD_DLL _declspec(dllexport)
#else
#define IMPLSERVERMETHOD_DLL _declspec(dllimport)
#endif

namespace serpents{

  class  XMLRPC_Method : public XmlRpc::XmlRpcServerMethod{
  public:
    std::mutex mtx;
    Method* method;
    XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s);
    void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);

    void fillParameterContainer(serpents::ParameterContainer& pc, XmlRpc::XmlRpcValue& params);
  };

  class  XmlRPC_CMethod : public xmlrpc_c::method {
  public:
    std::mutex mtx;
    Method* method;
    void setSignatureAndHelp();
    explicit XmlRPC_CMethod(Method* method);
    void execute(xmlrpc_c::paramList const& paramList,xmlrpc_c::value* const retvalP);
    void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
    ~XmlRPC_CMethod(){  }
  };

}

#endif // IMPLSERVERMETHOD_H_