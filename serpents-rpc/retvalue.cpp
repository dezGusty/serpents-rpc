#include "retValue.h"

XMLRPC_CRetValue::XMLRPC_CRetValue(){
	Impl_ = new Impl();
	
}
XMLRPC_CRetValue::~XMLRPC_CRetValue(){
	if (Impl_->value != nullptr)
		delete  Impl_->value;
	delete Impl_;
}

void XMLRPC_CRetValue::setValue(int n){
	Impl_->value = new xmlrpc_c::value_int(n);
}
void XMLRPC_CRetValue::setValue(double n){
	Impl_->value = new xmlrpc_c::value_double(n);
}
void XMLRPC_CRetValue::setValue(bool b){
	Impl_->value = new xmlrpc_c::value_boolean(b);
}
void XMLRPC_CRetValue::setValue(std::string s){
	Impl_->value = new xmlrpc_c::value_string(s);
}
xmlrpc_c::value* XMLRPC_CRetValue::getValue(){
	if (Impl_->value == nullptr)
		throw(std::exception("no return value"));
	return Impl_->value;
}


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
	if (!Impl_->value)
		throw(std::exception("no return value"));
	return Impl_->value;
}