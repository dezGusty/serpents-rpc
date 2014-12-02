
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
#include "guslib\system\dynamiclib.h"
#include "guslib\system\dynamiclibmanager.h"
#include "guslib/common/simpleexception.h"
#include "servermanager.h"
#include "serpents\rpc\server\rpcselector.h"
#include "serpents\rpc\server\server.h"
namespace serpents{
  void loadPlugin(const std::string& pluginName)
  {
    guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

    DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStartPlugin");

    if (!pFunc)
    {
      throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
    }

    // This must call installPlugin
    pFunc();
  }

  void unloadPlugin(const std::string& pluginName)
  {
    guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

    DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStopPlugin");

    if (!pFunc)
    {
      throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
    }

    // This must call installPlugin
    pFunc();
  }

  //plug in

  //choose impl of server 
  void RPCSelector::selectRPCMethod(Server& server, std::string plugInName){

    server_ = &server;

#ifdef USE_LOG4CPP
    auto map = server_->getLogTargets();
    for (auto it = map->begin(); it != map->end(); ++it){
      Log::getPtr()->addAppender(it->second, it->first);
    }
    Log::getPtr()->info("---using library " + plugInName + "---");
#endif

    std::cout << "start" << std::endl;
    loadPlugin(plugInName);
    std::cout << "loaded plugin: " << plugInName << std::endl;
    try{
      this->ServerStartUpImpl_ = serpents::ServerManager::getPtr()->getServerPointer(plugInName);
      server.setServerOptionsImpl(ServerStartUpImpl_->getImplServerOptions());
      server_->setServerOptionsImpl(ServerStartUpImpl_->getImplServerOptions()); //TODO this is silly, find a better way to do it
    }
    catch (std::exception& e){
      throw std::exception(e.what());
#ifdef USELOG4CPP
      Log::getPtr()->error(e.what());
#endif
    }
    if (ServerStartUpImpl_ == nullptr){
#ifdef USELOG4CPP
      Log::getPtr()->error("selected plugin was not found");
#endif
      throw std::exception("selected plugin was not found");
    }

  }
  void RPCSelector::stopServer(){
    // ServerStartUpImpl_->runCon = false;
  }

  void RPCSelector::startServer(){
    ServerStartUpImpl_->execute(server_);
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
