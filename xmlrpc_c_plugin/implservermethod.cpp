#include "..\xmlrpc_c_plugin\implservermethod.h"
#include "retvalue.h"
#include "serpents\rpc\parameters\parametercontainer.hpp"
#include <iostream>
#include "serpents\rpc\log\log.h"
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
		}
		catch (std::exception& e){
#ifdef USE_LOG4CPP //logging starts
			Log::getPtr()->info(std::string("In method ") + method->getName());
			Log::getPtr()->error(e.what());
#endif //logging ends; 
		}


#ifdef USE_LOG4CPP //logging starts
		Log::getPtr()->info(std::string("In method ") + method->getName());
		std::stringstream ss;
		ss << "  Input parameter: ";
		for each (auto var in pc.getAll()){
			ss << var << " ";
		}
		Log::getPtr()->info(ss.str());
		ss.str(std::string());
		ss.clear();
		int type = (*retvalP).type();
		switch (type){
			//int
		case xmlrpc_c::value::TYPE_INT: ss << "  Result: " << (static_cast<int>(static_cast<xmlrpc_c::value_int>(*(retvalP))));
			break;
			//bool
		case xmlrpc_c::value::TYPE_BOOLEAN:  ss << "  Result: " << (static_cast<bool>(static_cast<xmlrpc_c::value_boolean>(*(retvalP))));
			break;
			//double
		case xmlrpc_c::value::TYPE_DOUBLE:  ss << "  Result: " << (static_cast<double>(static_cast<xmlrpc_c::value_double>(*(retvalP))));
			break;
			//string
		case xmlrpc_c::value::TYPE_STRING:  ss << "  Result: " << (static_cast<std::string>(static_cast<xmlrpc_c::value_string>(*(retvalP))));
			break;
		}
		Log::getPtr()->info(ss.str());
		
#endif //logging ends; 
		mtx.unlock();
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
	
}