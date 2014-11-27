#ifndef XMLRPC_C_RETVALUE
#define XMLRPC_C_RETVALUE
#include "serpents\rpc\parameters\retValue.h"
#include "xmlrpc-c\base.hpp"

namespace serpents{

	class XMLRPC_CRetValue : public RetValue{
	public:
		void setValue(int n);
		void setValue(double n);
		void setValue(bool b);
		void setValue(std::string s);
		xmlrpc_c::value* getValue();
		XMLRPC_CRetValue();
		XMLRPC_CRetValue(const XMLRPC_CRetValue& retval) = delete;
		~XMLRPC_CRetValue();
	private:
		class Impl;
		Impl* Impl_;
	};
	
}

#endif // XMLRPC_C_RETVALUE