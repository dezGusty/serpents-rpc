#ifndef RPCSELECTOR_H
#define RPCSELECTOR_H




#ifdef SERPENTSRPC_EXPORTS
#define RPCSELECTDLL _declspec(dllexport)
#else
#define RPCSELECTDLL _declspec(dllimport)
#endif
#ifdef WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif


#include "serverstartup.h"
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
#endif



