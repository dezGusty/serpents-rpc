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

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <xmlrpc++/XmlRpc.h>

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include <fstream>
#include <thread>



#include <string>
#include "server.h"



namespace serpents{
	


	class  XMLRPC_Method : public XmlRpc::XmlRpcServerMethod{
	public:
		Method* method;
		XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s);
		void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);

		void fillParameterContainer(serpents::ParameterContainer& pc, XmlRpc::XmlRpcValue& params);
	};

	class  XmlRPC_CMethod : public xmlrpc_c::method {
	public:
		
		Method* method;
		void setSignatureAndHelp(){
			this->_signature = *method->signature;
			this->_help = *method->help;
		}
		XmlRPC_CMethod(Method* method) {
			this->_signature =*method->signature;
			this->_help = *method->help;
			this->method = method;
		}
		void execute(xmlrpc_c::paramList const& paramList,
			xmlrpc_c::value *   const  retvalP);

		void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
		~XmlRPC_CMethod(){	}
	};

	class RPCSELECTDLL ServerStartUp{
	protected: 
		class Impl;
		Impl* Impl_;
	public:
		bool runCon = true;
		ServerStartUp();
		virtual std::thread& execute(Server& server)=0;
		virtual void run(Server& server)=0;
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
	class RPCSELECTDLL RPCSelector
	{
	private:
		ServerStartUp* ServerStartUpImpl_;
	public:
		void startServer();
		void selectRPCMethod(Server& server, std::string method);
		void stopServer();
		RPCSelector();
		~RPCSelector();
	};



	
	class  XMLRPCpp_StartUp : public ServerStartUp{
	public:
		XmlRpc::XmlRpcServer* xmlServerPnt;
		std::thread& execute(Server& server);
		void controll();
		void run(Server& server);
	};
	
}
#endif



