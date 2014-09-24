
#ifndef IMPLSERVERMETHOD_H_
#define IMPLSERVERMETHOD_H_

#include "base.h"
#include "server.h"
#include "log.h"
#include "parametercontainer.h"
#include <string>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include <xmlrpc++/XmlRpc.h>
#include <sstream> 
#include <mutex>

#ifdef SERPENTSRPC_EXPORTS
#define IMPLSERVERMETHOD_DLL _declspec(dllexport)
#else
#define IMPLSERVERMETHOD_DLL _declspec(dllimport)
#endif

namespace serpents{

	class  XMLRPC_Method : public XmlRpc::XmlRpcServerMethod{
	public:
		std::mutex mtx;
		Method* method;
		XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s);
		void execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result);

		void fillParameterContainer(serpents::ParameterContainer& pc, XmlRpc::XmlRpcValue& params);
	};

	class  XmlRPC_CMethod : public xmlrpc_c::method {
	public:
		std::mutex mtx;
		Method* method;
		void setSignatureAndHelp();
		explicit XmlRPC_CMethod(Method* method);
		void execute(xmlrpc_c::paramList const& paramList,xmlrpc_c::value* const retvalP);
		void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
		~XmlRPC_CMethod(){	}
	};

}

#endif // IMPLSERVERMETHOD_H_