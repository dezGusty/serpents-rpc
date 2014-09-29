#ifndef RETVALUE_H_
#define RETVALUE_H_

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
