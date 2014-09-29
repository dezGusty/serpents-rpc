#ifndef IMPLSERVERMETHOD_H_
#define IMPLSERVERMETHOD_H_

//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

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