#ifndef RPCSELECTOR_H_
#define RPCSELECTOR_H_

#ifdef SERPENTSRPC_EXPORTS
#define RPCSELECTDLL _declspec(dllexport)
#else
#define RPCSELECTDLL _declspec(dllimport)
#endif
//serpents libs
#include "serpents/rpc/server/serverstartup.h"
#ifdef USE_LOG4CPP
#include "serpents/rpc/log/log.h"
#endif

//c++ system libs
#ifdef WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif
#include <stdexcept>
#include <iostream>
#include <string>
#include <cassert>
namespace serpents{
  class ServerStartUp;
  

  class RPCSELECTDLL RPCSelector
  {
  private:
    ServerStartUp* ServerStartUpImpl_;
    Server* server_;
  public:
    void startServer();
    void selectRPCMethod(Server& server, std::string method);
    void stopServer();
    RPCSelector();
    ~RPCSelector();
  };
}
#endif  // RPCSELECTOR_H_



