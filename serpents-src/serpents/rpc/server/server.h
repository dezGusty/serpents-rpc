#ifndef SERVER_H_
#define SERVER_H_

//serpents libs
#include "serpents/rpc/base.h"
#include "serpents/rpc/server/repository.h"
#include "serpents/rpc/server/serveroptions.h"
//c++ sytem libs
#include <thread>
#include <string>


#ifdef SERPENTSRPC_EXPORTS
#define SERVERDLL _declspec(dllexport)
#else
#define SERVERDLL _declspec(dllimport)
#endif


namespace serpents{
  
  class SERVERDLL Server{
    class Impl;
    Impl* Impl_;
      
    FunctionRepository* repository;
  public:
    Server();
    Server(unsigned int port);
    void run();
    std::string getURI();
    unsigned int getPort();
    void setURI(std::string URI);
    void setPort(const unsigned int Port);
    void setRepository(FunctionRepository& fr);
    FunctionRepository* getRepository();
    XMLRPC_CServerOptions* getXMLRPC_CServerOptions();
    XMLRPCPP_ServerOptions* getXMLRPCPP_ServerOptions();
    void addLogTarget(std::string type, std::string fileName);
    std::map<std::string, std::string>* getLogTargets();
  };
  class Server::Impl{
  public:
    std::string URI;
    unsigned int port;
    std::map<std::string, std::string> logmap;
    XMLRPC_CServerOptions* soPtr;
    XMLRPCPP_ServerOptions* socppPtr;
  };

}

#endif

    