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

// system libs
#include <mutex>
#include <algorithm>
#include <map>
#include <string>

// project libs
#include "xmlrpc_c_startup.h"
#include "serpents\rpc\server\server.h"
#include "guslib\util\pluginmanager.h"
#include "servermanager.h"
#include "xmlrpc_c_serveroptions.h"
#include "xmlrpc_c_buildopts.h"
#include "serpents\rpc\log\log.h"
namespace serpents
{
  class XMLRPC_C_StartUp::Impl
  {
    friend XMLRPC_C_StartUp;
    std::thread controllThread ;
    std::thread thrd;
    xmlrpc_c::serverAbyss* serverAbyssPtr = nullptr;
    bool runCon =false;
    xmlrpc_c::registry myRegistry;
    XMLRPC_CServerOptions serveroptions;
  };

  XMLRPC_C_StartUp::XMLRPC_C_StartUp()
  {
    Impl_ = new Impl;
  }
  XMLRPC_C_StartUp::~XMLRPC_C_StartUp()
  {
    delete Impl_;
  }
  ServerOptions* XMLRPC_C_StartUp::getImplServerOptions()
  {
    return &Impl_->serveroptions;
  }

  void XMLRPC_C_StartUp::run(serpents::Server* server)
  {
    try
    {
      FunctionRepository* fr = server->getRepository();
      std::map<std::string, Method *>::iterator it;
      for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it)
      {
        Impl_->myRegistry.addMethod(it->first, new XmlRPC_CMethod(it->second));
      }
      Impl_->serveroptions.getConstrOpt()->registryP(&Impl_->myRegistry);
      xmlrpc_c::serverAbyss myAbyssServer(*Impl_->serveroptions.getConstrOpt());
      Impl_->serverAbyssPtr = &myAbyssServer;
      std::mutex mtx;
      while (Impl_->runCon)
      {
        mtx.lock();
        myAbyssServer.runOnce();
        mtx.unlock();
      }
    }
    catch (const std::exception const& e)
    {
      e.what();
#ifdef USELOG4CPP
     
      Log::getPtr()->error(e.what());
#endif
    }
  }  //  run()

  std::thread& XMLRPC_C_StartUp::execute(serpents::Server* server)
  {
    Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);
    Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this, server);
    return Impl_->thrd;
  }  //  (execute())

  void XMLRPC_C_StartUp::start()
  {
    Impl_->controllThread.join();
  }
  void XMLRPC_C_StartUp::stop()
  {
    //  haven't decided what to do with this yet.
  }
  void XMLRPC_C_StartUp::controll()
  {
    std::cout << "Type \"exit\" to exit" << std::endl;
    bool keppAlive = true;
    bool isFirst = true;
    while (keppAlive)
    {
      std::string command;
      if (Impl_->serverAbyssPtr != nullptr)
      {
        if (isFirst)
        {
          std::cout << "server started" << std::endl;
#ifdef USELOG4CPP
          Log::getPtr()->info("server started");
#endif
          isFirst = false;
        }
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (strcmp(command.c_str(), "exit") == 0)
        {
          Impl_->serverAbyssPtr->terminate();
          std::cout << "server closed" << std::endl;
#ifdef USELOG4CPP
          Log::getPtr()->info("server closed");
#endif
          keppAlive = false;
        }
      }
      std::this_thread::yield();
    }
  }  //  controll()

  //  Plugin overrides
  XMLRPC_C_StartUp* xmlrpc_c_plugin_Inst = nullptr;
  std::string hiddenName = "xmlrpc_plugin";

  const std::string& XMLRPC_C_StartUp::getName() const
  {
    return hiddenName;
  }

  void XMLRPC_C_StartUp::install()
  {
    ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);
  }

  void XMLRPC_C_StartUp::initialize()
  {
    //  ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);  //  install already does this
  }

  void XMLRPC_C_StartUp::shutdown()
  {
    // filler method for now
  }

  void XMLRPC_C_StartUp::uninstall()
  {
    delete xmlrpc_c_plugin_Inst;
    xmlrpc_c_plugin_Inst = nullptr;
  }

  //-----------------------------------------------------------------------
  extern "C" void PLUGINXMLRPC_C_EXPORT_SYMBOL dllStartPlugin(void)
  {
    // Create new plugin
    xmlrpc_c_plugin_Inst = new XMLRPC_C_StartUp();
    guslib::PluginManager::get().install(xmlrpc_c_plugin_Inst);

    // Register
  }
  extern "C" void PLUGINXMLRPC_C_EXPORT_SYMBOL dllStopPlugin(void)
  {
    guslib::PluginManager::get().uninstall(xmlrpc_c_plugin_Inst);
    delete xmlrpc_c_plugin_Inst;
    xmlrpc_c_plugin_Inst = nullptr;
  }
}

