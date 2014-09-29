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

#include "serveroptions.h"


namespace serpents{
  XMLRPC_CServerOptions::XMLRPC_CServerOptions(){
    constrOpt_ = new constrOpt();
    constrOpt_->portNumber(8081);
  }
  void XMLRPC_CServerOptions::portNumber(unsigned int   const& arg){
    constrOpt_->portNumber(arg);
  }
  void  XMLRPC_CServerOptions::logFileName(std::string    const& arg){
    constrOpt_->logFileName(arg);
  }
  void  XMLRPC_CServerOptions::keepaliveTimeout(unsigned int   const& arg){
    constrOpt_->keepaliveTimeout(arg);
  }
  void XMLRPC_CServerOptions::keepaliveMaxConn(unsigned int   const& arg){
    constrOpt_->keepaliveMaxConn(arg);
  }
  void XMLRPC_CServerOptions::timeout(unsigned int   const& arg){
    constrOpt_->timeout(arg);
  }
  void XMLRPC_CServerOptions::dontAdvertise(bool           const& arg){
    constrOpt_->dontAdvertise(arg);
  }
  void XMLRPC_CServerOptions::uriPath(std::string    const& arg){
    constrOpt_->uriPath(arg);
  }
  void XMLRPC_CServerOptions::chunkResponse(bool const& arg){
    constrOpt_->chunkResponse(arg);
  }
  void XMLRPC_CServerOptions::allowOrigin(std::string    const& arg){
    constrOpt_->allowOrigin(arg);
  }
  void XMLRPC_CServerOptions::accessCtlMaxAge(unsigned int const& arg){
    constrOpt_->accessCtlMaxAge(arg);
  }
  void XMLRPC_CServerOptions::serverOwnsSignals(bool const& arg){
    constrOpt_->serverOwnsSignals(arg);
  }
  void XMLRPC_CServerOptions::expectSigchld(bool const& arg){
    constrOpt_->expectSigchld(arg);
  }
  xmlrpc_c::serverAbyss::constrOpt* XMLRPC_CServerOptions::getConstrOpt(){
    return this->constrOpt_;
  }


  void XMLRPCPP_ServerOptions::setPort(unsigned int port){
    if (port < 65535)
      Impl_->portNum = port;
    else
      throw std::exception("port number out of range");
  }
  unsigned int XMLRPCPP_ServerOptions::getPort(){
    return Impl_->portNum;
  }
  XMLRPCPP_ServerOptions::XMLRPCPP_ServerOptions(){
    Impl_ = new Impl;
    Impl_->portNum = 8080;
  }
  XMLRPCPP_ServerOptions::~XMLRPCPP_ServerOptions(){
    delete Impl_;
  }
}