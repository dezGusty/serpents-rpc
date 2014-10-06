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

#include "serverstartup.h"
namespace serpents{
  void ServerStartUp::start(){
    this->Impl_->controllThread.join();

  }
  ServerStartUp::ServerStartUp(){
    Impl_ = new Impl();
  }
  
  void XMLRPC_C_StartUp::run(Server& server){
    try {

      FunctionRepository* fr = server.getRepository();
      xmlrpc_c::registry myRegistry;
      std::map<std::string, Method *>::iterator it;
      for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
        xmlrpc_c::methodPtr const xmlRPCMEthodPtr(new XmlRPC_CMethod(it->second));
        myRegistry.addMethod(it->first, xmlRPCMEthodPtr);
      }
      xmlrpc_c::serverAbyss::constrOpt conOpt = *server.getXMLRPC_CServerOptions()->getConstrOpt();
      xmlrpc_c::serverAbyss myAbyssServer(conOpt.registryP(&myRegistry));
      //  .registryP(&myRegistry)
      //  .portNumber(server.getPort()));
      this->serverAbyssPtr = &myAbyssServer; //change to set/get
      
      std::mutex mtx;
      while (runCon){
        mtx.lock();
        myAbyssServer.runOnce();
        // xmlrpc_c::serverAbyss.run() never returns
        mtx.unlock();

      }

    }
    catch (std::exception const& e) {
      std::cerr << "Something failed.  " << e.what() << std::endl;
    }
  }



  std::thread& XMLRPC_C_StartUp::execute(Server& server){
    Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);

    Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this, server);
    return Impl_->thrd;
  }

  void XMLRPC_C_StartUp::controll(){
    std::cout << "Type \"exit\" to exit" << std::endl;
    bool keppAlive = true;
    bool isFirst = true;
    while (keppAlive){
      std::string command;
      if (serverAbyssPtr != nullptr){
        if (isFirst){
          std::cout << "server started" << std::endl;
          isFirst = false;
        }
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (strcmp(command.c_str(), "exit") == 0){
          this->serverAbyssPtr->terminate();
          std::cout << "server closed" << std::endl;
          keppAlive = false;
        }

      }
      std::this_thread::yield();
    }

  }

  std::thread& XMLRPCpp_StartUp::execute(Server& server){

    Impl_->controllThread = std::thread(&XMLRPCpp_StartUp::controll, this);

    Impl_->thrd = std::thread(&XMLRPCpp_StartUp::run, this, server);
    return Impl_->thrd;

  }

  void XMLRPCpp_StartUp::run(Server& server){

    try {
      XmlRpc::XmlRpcServer s;
      FunctionRepository* fr = server.getRepository();

      std::map<std::string, Method *>::iterator it;
      for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
        XMLRPC_Method* b = new XMLRPC_Method(it->second, it->first, &s);
        s.addMethod(b);
      }

      s.bindAndListen(8081);
      s.enableIntrospection(true);
      xmlServerPnt = &s;
      
      //TODO: Figure out what that means
      s.work(-1.0);
    }
    catch (std::exception const& e) {
      std::cerr << "Something failed.  " << e.what() << std::endl;
    }

  }
  void XMLRPCpp_StartUp::controll(){

    std::cout << "Type \"exit\" to exit" << std::endl;

    bool keppAlive = true;
    bool isFirst = true;
    while (keppAlive){
      std::string command;
      if (xmlServerPnt != nullptr){
        if (isFirst){
          std::cout << "server started" << std::endl;
          isFirst = false;
        }
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (strcmp(command.c_str(), "exit") == 0){
          this->xmlServerPnt->shutdown();
          std::cout << "server closed" << std::endl;
          keppAlive = false;
        }

      }
      std::this_thread::yield();
    }
  }
  
}