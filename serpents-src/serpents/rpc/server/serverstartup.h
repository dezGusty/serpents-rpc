#ifndef SERVERSTARTUP_H_
#define SERVERSTARTUP_H_

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