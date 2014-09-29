#ifndef RETVALUE_H_
#define RETVALUE_H_
//serpents libs
#include "serpents/rpc/base.h"

//xmlrpc-c libs
#include <xmlrpc-c/base.hpp>

//xmlrpc++ libs
#include <xmlrpc++/XmlRpc.h>

//c++ system libs
#include <string>

#ifdef SERPENTSRPC_EXPORTS
#define RET_VALUE_DLL _declspec(dllexport)
#else
#define RET_VALUE_DLL _declspec(dllimport)
#endif
class RET_VALUE_DLL RetValue{
public:
  virtual void setValue(int n) = 0;
  virtual void setValue(double n) = 0; 
  virtual void setValue(bool b) = 0; 
  virtual void setValue(std::string s) = 0; 

};


class XMLRPC_CRetValue: public RetValue{
public:
  void setValue(int n);
  void setValue(double n);
  void setValue(bool b);
  void setValue(std::string s);
  xmlrpc_c::value* getValue();
  XMLRPC_CRetValue();
  ~XMLRPC_CRetValue();
private:
  class Impl;
  Impl* Impl_;
};
class XMLRPC_CRetValue::Impl{
  friend XMLRPC_CRetValue;
  xmlrpc_c::value* value;
};

class XMLRPC_CPPRetValue: public RetValue{
public:
  void setValue(int n);
  void setValue(double n);
  void setValue(bool b);
  void setValue(std::string s);
  XmlRpc::XmlRpcValue getValue();
  XMLRPC_CPPRetValue();
  ~XMLRPC_CPPRetValue();
private:
  class Impl;
  Impl* Impl_;
  
};

class XMLRPC_CPPRetValue::Impl{
  friend XMLRPC_CPPRetValue;
  XmlRpc::XmlRpcValue value;
};

#endif  // RETVALUE_H_
