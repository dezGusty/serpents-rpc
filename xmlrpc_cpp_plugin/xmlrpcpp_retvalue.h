#ifndef XMLRPCPP_RETVALUE_H_
#define XMLRPCPP_RETVALUE_H_
//serpents libs
#include "serpents\rpc\parameters\retValue.h"

//xmlrpc++ libs
#include "xmlrpc++\XmlRpc.h"

namespace serpents {
	class XMLRPC_CPPRetValue : public RetValue{
	public:
		void setValue(int n);
		void setValue(double n);
		void setValue(bool b);
		void setValue(std::string s);
		XmlRpc::XmlRpcValue getValue();
		XMLRPC_CPPRetValue();
		~XMLRPC_CPPRetValue();
	private:
		class Impl;
		Impl* Impl_;


	};
}

#endif //XMLRPCPP_RETVALUE_H_