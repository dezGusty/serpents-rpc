#ifndef SERVERSTARTUP_H_
#define SERVERSTARTUP_H_

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
#include "serpents/rpc/server/implservermethod.h"

//c++ system libs
#include <iostream>
#include <thread>
#include <algorithm>
#ifdef SERPENTSRPC_EXPORTS
#define SERVERSTARTUP_DLL _declspec(dllexport)
#else
#define SERVERSTARTUP_DLL _declspec(dllimport)
#endif

namespace serpents{
  
  class SERVERSTARTUP_DLL ServerStartUp{
  protected:
    class Impl;
    Impl* Impl_;
  public:
    bool runCon = true;
    ServerStartUp();
      
    virtual std::thread& execute(Server& server) = 0;
    virtual void run(Server& server) = 0;
    void start();
  };

  class ServerStartUp::Impl{
  public:
    std::thread thrd;
    std::thread controllThread;
  };

  class  XMLRPC_C_StartUp : public ServerStartUp{
  public:
    xmlrpc_c::serverAbyss* serverAbyssPtr;
    std::thread& execute(Server& server);
    void controll();
    void run(Server& server);
    
  };


  class  XMLRPCpp_StartUp : public ServerStartUp{
  public:
    XmlRpc::XmlRpcServer* xmlServerPnt;
    std::thread& execute(Server& server);
    void controll();
    void run(Server& server);
    
  };

}

#endif  // SERVERSTARTUP_H_