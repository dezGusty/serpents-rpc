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
#include "serpents/rpc/parameters/retValue.h"

XMLRPC_CRetValue::XMLRPC_CRetValue(){
  Impl_ = new Impl();
  
}
XMLRPC_CRetValue::~XMLRPC_CRetValue(){
  if (Impl_->value != nullptr)
    delete  Impl_->value;
  delete Impl_;
}

void XMLRPC_CRetValue::setValue(int n){
  Impl_->value = new xmlrpc_c::value_int(n);
}
void XMLRPC_CRetValue::setValue(double n){
  Impl_->value = new xmlrpc_c::value_double(n);
}
void XMLRPC_CRetValue::setValue(bool b){
  Impl_->value = new xmlrpc_c::value_boolean(b);
}
void XMLRPC_CRetValue::setValue(std::string s){
  Impl_->value = new xmlrpc_c::value_string(s);
}
xmlrpc_c::value* XMLRPC_CRetValue::getValue(){
  if (Impl_->value == nullptr)
    throw(std::exception("no return value"));
  return Impl_->value;
}


XMLRPC_CPPRetValue::XMLRPC_CPPRetValue(){
  Impl_ = new Impl();
}
XMLRPC_CPPRetValue::~XMLRPC_CPPRetValue(){
  delete Impl_;
}

void XMLRPC_CPPRetValue::setValue(int n){
  Impl_->value = XmlRpc::XmlRpcValue(n);
}
void XMLRPC_CPPRetValue::setValue(double n){
  Impl_->value = XmlRpc::XmlRpcValue(n);
}
void XMLRPC_CPPRetValue::setValue(bool b){
  Impl_->value = XmlRpc::XmlRpcValue(b);
}
void XMLRPC_CPPRetValue::setValue(std::string s){
  Impl_->value = XmlRpc::XmlRpcValue(s);
}
XmlRpc::XmlRpcValue XMLRPC_CPPRetValue::getValue(){
  if (!Impl_->value)
    throw(std::exception("no return value"));
  return Impl_->value;
}