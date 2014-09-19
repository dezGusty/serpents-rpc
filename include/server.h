#ifndef SERVER_H
#define SERVER_H
#define SERVER_EXPORT
#ifdef SERVER_EXPORT
#define SERVERDLL _declspec(dllexport)
#else
#define SERVERDLL _declspec(dllimport)
#endif

#include "base.h"
#include <thread>
#include <string>
#include "repository.h"
#include "serveroptions.h"

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

	};
	class Server::Impl{
	public:
		std::string URI;
		unsigned int port;
		XMLRPC_CServerOptions* soPtr;
		XMLRPCPP_ServerOptions* socppPtr;
	};

}

#endif

		