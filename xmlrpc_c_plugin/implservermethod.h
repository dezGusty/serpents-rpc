#ifndef XMLRPC_C_IMPLSERVMETHOD_H_
#define XMLRPC_C_IMPLSERVMETHOD_H_

//sys libs
#include <mutex>

//project libs
#include "xmlrpc-c\server_abyss.hpp"
#include "serpents\rpc\server\method.hpp"
namespace serpents{
	class  XmlRPC_CMethod : public xmlrpc_c::method {
	public:
		std::mutex mtx;
		Method* method;
		void setSignatureAndHelp();
		explicit XmlRPC_CMethod(Method* method);
		void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP);
		void fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList);
		~XmlRPC_CMethod(){  }
	};
}
#endif // XMLRPC_C_IMPLSERVMETHOD_H_