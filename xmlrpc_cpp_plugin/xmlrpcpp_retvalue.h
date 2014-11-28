#ifndef XMLRPCPP_RETVALUE_H_
#define XMLRPCPP_RETVALUE_H_
//serpents libs
#include "serpents\rpc\parameters\retValue.h"

//xmlrpc++ libs
#include "xmlrpc++\XmlRpc.h"

namespace serpents {
  class XMLRPC_CPPRetValue : public RetValue{
  public:
    void setValue(int n) override;
    void setValue(double n) override;
    void setValue(float f ) override;
    void setValue(bool b) override;
    void setValue(std::string s) override;
    XmlRpc::XmlRpcValue getValue();
    XMLRPC_CPPRetValue(const XMLRPC_CPPRetValue&) = delete;
    XMLRPC_CPPRetValue();
    ~XMLRPC_CPPRetValue();
  private:
    class Impl;
    Impl* Impl_;


  };
}

#endif //XMLRPCPP_RETVALUE_H_