#include "implservermethod.h"

namespace serpents{
	void XmlRPC_CMethod::execute(xmlrpc_c::paramList const& paramList,
		xmlrpc_c::value *   const  retvalP) {

		serpents::ParameterContainer pc;
		fillParameterContainer(pc, paramList);
		XMLRPC_CRetValue rv;
		method->execute(pc, rv);
		*retvalP = *(rv.getValue());

	}
	void XmlRPC_CMethod::fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList){

		int parameterListSize(paramList.size());
		for (int i = 0; i < parameterListSize; i++){
			xmlrpc_c::value value = paramList[i];
			int type = value.type();
			switch (type){
				//int
			case xmlrpc_c::value::TYPE_INT: pc.add(paramList.getInt(i));  break;
				//bool
			case xmlrpc_c::value::TYPE_BOOLEAN: paramList.getBoolean(i); break;
				//double
			case xmlrpc_c::value::TYPE_DOUBLE: pc.add(paramList.getDouble(i));  break;
				//string
			case xmlrpc_c::value::TYPE_STRING: pc.add(paramList.getString(i));  break;
			}

		}
	}


	XMLRPC_Method::XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s) :XmlRpc::XmlRpcServerMethod(methodName, s){
		if (method != nullptr)
			this->method = method;
	}
	void XMLRPC_Method::execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result){

		serpents::ParameterContainer pc;
		XMLRPC_CPPRetValue rv;
		fillParameterContainer(pc, params);
		method->execute(pc, rv);
		result = rv.getValue();

	}
	void XMLRPC_Method::fillParameterContainer(serpents::ParameterContainer& pc, XmlRpc::XmlRpcValue& params){

		int paramSize = params.size();
		for (int i = 0; i < paramSize; ++i){
			switch (params[i].getType()){
				//int
			case XmlRpc::XmlRpcValue::Type::TypeInt: pc.add(int(params[i]));  break;
				//bool
			case  XmlRpc::XmlRpcValue::Type::TypeBoolean: pc.add(bool(params[i])); break;
				//double
			case  XmlRpc::XmlRpcValue::Type::TypeDouble: pc.add(double(params[i]));  break;
				//string
			case  XmlRpc::XmlRpcValue::Type::TypeString: pc.add(std::string(params[i]));  break;
			}
		}
	}
}