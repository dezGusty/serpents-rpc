//serpents libs 
#include "implservermethod.h"
#include "xmlrpcpp_retvalue.h"

namespace serpents{

	XMLRPC_Method::XMLRPC_Method(Method* method, std::string methodName, XmlRpc::XmlRpcServer* s) 
		:XmlRpc::XmlRpcServerMethod(methodName, s)
	{
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
		ss << "  Input parameter: ";
		for each (auto var in pc.getAll()){
			ss << var << " ";
		}
		Logger::getInstance().info(ss.str());
		ss.str(std::string());
		ss.clear();
		ss << "  Result: ";
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