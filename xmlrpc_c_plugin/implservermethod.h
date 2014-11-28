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

#ifndef XMLRPC_C_IMPLSERVMETHOD_H_
#define XMLRPC_C_IMPLSERVMETHOD_H_

//  sys libs
#include <mutex>

//  project libs
#include "xmlrpc-c\server_abyss.hpp"
#include "serpents\rpc\server\method.hpp"
namespace serpents
{
  class  XmlRPC_CMethod : public xmlrpc_c::method 
  {
    public:
    Method* method;
    void setSignatureAndHelp();
    explicit XmlRPC_CMethod(Method* method);
    XmlRPC_CMethod();
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP);
    void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
    ~XmlRPC_CMethod(){  }
  };
}
#endif // XMLRPC_C_IMPLSERVMETHOD_H_