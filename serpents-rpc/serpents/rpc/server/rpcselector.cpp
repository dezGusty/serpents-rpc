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

#include "RPCSelector.h"

namespace serpents{
  class ServerStartUp;
  //choose impl of server 
  void RPCSelector::selectRPCMethod(Server& server, std::string method){
    server_ = &server;
    if (strcmp(method.c_str(), "xmlrpc_c") == 0){
      ServerStartUpImpl_ = new XMLRPC_C_StartUp();
      
    }
    if (strcmp(method.c_str(), "xmlrpc++") == 0){

      ServerStartUpImpl_ = new XMLRPCpp_StartUp();
    }
#ifdef USE_LOG4CPP
    auto map = server.getLogTargets();
    for (auto it = map->begin(); it != map->end(); ++it){
      Logger::getInstance().addAppender(it->second,it->first);
    }
    Logger::getInstance().info("---using library "+ method+"---");
#endif

  }
  void RPCSelector::stopServer(){
    ServerStartUpImpl_->runCon = false;
  }

  void RPCSelector::startServer(){
    ServerStartUpImpl_->execute(*server_);
    ServerStartUpImpl_->start();
  }
  RPCSelector::RPCSelector()
  {
  }


  RPCSelector::~RPCSelector()
  {
    delete ServerStartUpImpl_;
    
  }


  

  


}