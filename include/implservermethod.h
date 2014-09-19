#ifndef IMPLSERVERMETHOD_H
#define IMPLSERVERMETHOD_H
#pragma once
#include "base.h"
#include "server.h"
#include <xmlrpc++/XmlRpc.h>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#ifdef SERPENTSRPC_EXPORTS
#define IMPLSERVERMETHOD_DLL _declspec(dllexport)
#else
#define IMPLSERVERMETHOD_DLL _declspec(dllimport)
#endif
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
			this->_signature = method->getSignature();
			this->_help = method->getHelp();
		}
		XmlRPC_CMethod(Method* method) {
			this->_signature = method->getSignature();
			this->_help = method->getHelp();
			this->method = method;
		}
		void execute(xmlrpc_c::paramList const& paramList,
			xmlrpc_c::value *   const  retvalP);

		void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
		~XmlRPC_CMethod(){	}
	};

}

#endif