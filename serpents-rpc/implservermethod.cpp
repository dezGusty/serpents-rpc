#include "implservermethod.h"

namespace serpents{
	void XmlRPC_CMethod::execute(xmlrpc_c::paramList const& paramList, //execute
		xmlrpc_c::value *   const  retvalP) {
		mtx.lock();
		serpents::ParameterContainer pc;
		try{			
			fillParameterContainer(pc, paramList);
			XMLRPC_CRetValue rv;
			method->execute(&pc, &rv); //execute
			*retvalP = *(rv.getValue());
		}catch (std::exception& e){
#ifdef USE_LOG4CPP //logging starts
			Logger::getInstance().info(std::string("In method ") + method->getName());
			Logger::getInstance().error(e.what());
#endif //logging ends; 
		}
		

#ifdef USE_LOG4CPP //logging starts
		Logger::getInstance().info(std::string("In method ") + method->getName());
		std::stringstream ss;
		ss << "	Input parameter: ";
		for each (auto var in pc.getAll()){
			ss << var << " ";
		}
		Logger::getInstance().info(ss.str());
		ss.str(std::string());
		ss.clear();
		int type = (*retvalP).type();
		switch (type){
			//int
		case xmlrpc_c::value::TYPE_INT: ss << "	Result: " <<( static_cast<int>(static_cast<xmlrpc_c::value_int>(*(retvalP)))); 
			break;
			//bool
		case xmlrpc_c::value::TYPE_BOOLEAN:  ss << "	Result: " << (static_cast<bool>(static_cast<xmlrpc_c::value_boolean>(*(retvalP))));
			break;
			//double
		case xmlrpc_c::value::TYPE_DOUBLE:  ss << "	Result: " << (static_cast<double>(static_cast<xmlrpc_c::value_double>(*(retvalP)))); 
			break;
			//string
		case xmlrpc_c::value::TYPE_STRING:  ss << "	Result: " << (static_cast<std::string>(static_cast<xmlrpc_c::value_string>(*(retvalP)))); 
			break;
		}
		Logger::getInstance().info(ss.str());
		mtx.unlock();
#endif //logging ends; 

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
			case xmlrpc_c::value::TYPE_BOOLEAN: pc.add(paramList.getBoolean(i)); break;
				//double
			case xmlrpc_c::value::TYPE_DOUBLE: pc.add(paramList.getDouble(i));  break;
				//string
			case xmlrpc_c::value::TYPE_STRING: pc.add(paramList.getString(i));  break;
			}

		}
	}
	void XmlRPC_CMethod::setSignatureAndHelp(){
		this->_signature = method->getSignature();
		this->_help = method->getHelp();
	}
	 XmlRPC_CMethod::XmlRPC_CMethod(Method* method) {
		this->_signature = method->getSignature();
		this->_help = method->getHelp();
		this->method = method;
	}


	XMLRPC_Method::XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s) :XmlRpc::XmlRpcServerMethod(methodName, s){
		if (method != nullptr)
			this->method = method;
	}
	void XMLRPC_Method::execute(XmlRpc::XmlRpcValue& params, XmlRpc::XmlRpcValue& result){
		mtx.lock();
		serpents::ParameterContainer pc;
		XMLRPC_CPPRetValue rv;
		fillParameterContainer(pc, params);
		try{
			method->execute(&pc, &rv);
			result = rv.getValue();
		}catch (std::exception& e){

#ifdef USE_LOG4CPP // start logging 
			Logger::getInstance().error("In method "+method->getName()+" "+ e.what());
#endif // end logging 
		}
		mtx.unlock();
#ifdef USE_LOG4CPP // start logging 
		Logger::getInstance().info(std::string("In method ") + method->getName());
		std::stringstream ss;
		ss << "	Input parameter: ";
		for each (auto var in pc.getAll()){
			ss << var << " ";
		}
		Logger::getInstance().info(ss.str());
		ss.str(std::string());
		ss.clear();
		ss << "	Result: ";
		int type = result.getType();
		switch (type){
			//int
		case XmlRpc::XmlRpcValue::Type::TypeInt:ss<< (static_cast<int>(result));  break;
			//bool
		case  XmlRpc::XmlRpcValue::Type::TypeBoolean:ss << (static_cast<bool>(result)); break;
			//double
		case  XmlRpc::XmlRpcValue::Type::TypeDouble:ss << (static_cast<double>(result));  break;
			//string
		case  XmlRpc::XmlRpcValue::Type::TypeString:ss << (static_cast<std::string>(result));  break;
		}
		Logger::getInstance().info(ss.str());
#endif  // end logging 

	}
	void XMLRPC_Method::fillParameterContainer(serpents::ParameterContainer& pc, XmlRpc::XmlRpcValue& params){

		int paramSize = params.size();
		for (int i = 0; i < paramSize; ++i){
			switch (params[i].getType()){
				//int
			case XmlRpc::XmlRpcValue::Type::TypeInt: pc.add(static_cast<int>(params[i]));  break;
				//bool
			case  XmlRpc::XmlRpcValue::Type::TypeBoolean: pc.add(static_cast<bool>(params[i])); break;
				//double
			case  XmlRpc::XmlRpcValue::Type::TypeDouble: pc.add(static_cast<double>(params[i]));  break;
				//string
			case  XmlRpc::XmlRpcValue::Type::TypeString: pc.add(static_cast<std::string>(params[i]));  break;
			}
		}
	}
}