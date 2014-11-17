#include "xmlrpcpp_retvalue.h"

namespace serpents {
	class XMLRPC_CPPRetValue::Impl{
		friend XMLRPC_CPPRetValue;
		XmlRpc::XmlRpcValue value;
	};
	XMLRPC_CPPRetValue::XMLRPC_CPPRetValue(){
		Impl_ = new Impl();
	}
	XMLRPC_CPPRetValue::~XMLRPC_CPPRetValue(){
		delete Impl_;
	}

	void XMLRPC_CPPRetValue::setValue(int n){
		Impl_->value = XmlRpc::XmlRpcValue(n);
	}
	void XMLRPC_CPPRetValue::setValue(double n){
		Impl_->value = XmlRpc::XmlRpcValue(n);
	}
	void XMLRPC_CPPRetValue::setValue(bool b){
		Impl_->value = XmlRpc::XmlRpcValue(b);
	}
	void XMLRPC_CPPRetValue::setValue(std::string s){
		Impl_->value = XmlRpc::XmlRpcValue(s);
	}
	XmlRpc::XmlRpcValue XMLRPC_CPPRetValue::getValue(){
		if (!Impl_->value.valid())
			throw(std::exception("no return value"));
		return Impl_->value;
	}

}