#include "stdafx.h"
#include "RPCSelector.h"
#include <future>

namespace serpents{
	
	void RPCSelector::selectRPCMethod(Server& server, std::string method){

		//ServerStartUp* startUp =nullptr;
		if (strcmp(method.c_str(), "xmlrpc_c") == 0){
			ServerStartUpImpl_ = new XMLRPC_C_StartUp();
			//startUp = dynamic_cast<XMLRPC_C_StartUp*>(ServerStartUpImpl_);
			ServerStartUpImpl_->execute(server);
			//this->ServerStartUpImpl_ = startUp;
		}
		if (strcmp(method.c_str(), "xmlrpc++") == 0){
			
			ServerStartUpImpl_ = new XMLRPCpp_StartUp();
			//startUp = dynamic_cast<XMLRPCpp_StartUp*>(ss);
			ServerStartUpImpl_->execute(server);
			//this->ServerStartUpImpl_ = startUp;
		}
		
	}
	void RPCSelector::stopServer(){
		assert(ss != nullptr);
		ServerStartUpImpl_->runCon = false;
	}

	void RPCSelector::startServer(){
		ServerStartUpImpl_->start();
	}
	RPCSelector::RPCSelector()
	{
	}


	RPCSelector::~RPCSelector()
	{
		delete ServerStartUpImpl_;
	}

	void ServerStartUp::start(){
		{ this->Impl_->controllThread.join(); }
	}
	ServerStartUp::ServerStartUp(){
		Impl_ = new Impl();
	}

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
	void XMLRPC_C_StartUp::run(Server& server){
		try {

			FunctionRepository* fr = server.getRepository();
			xmlrpc_c::registry myRegistry;
			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				xmlrpc_c::methodPtr const xmlRPCMEthodPtr(new XmlRPC_CMethod(it->second));
				myRegistry.addMethod(it->first, xmlRPCMEthodPtr);
			}
			xmlrpc_c::serverAbyss myAbyssServer(
				xmlrpc_c::serverAbyss::constrOpt()
				.registryP(&myRegistry)
				.portNumber(server.getPort()));
			this->serverAbyssPtr = &myAbyssServer; //change to set/get
			
			while (runCon){
				myAbyssServer.runOnce();
				// xmlrpc_c::serverAbyss.run() never returns
				assert(false);
			}

		}
		catch (std::exception const& e) {
			std::cerr << "Something failed.  " << e.what() << std::endl;
		}
	}

	 

	std::thread& XMLRPC_C_StartUp::execute(Server& server){
		Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);
		
		Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this,server);
		return Impl_->thrd;
	}

	void XMLRPC_C_StartUp::controll(){
		std::cout << "Type \"exit\" to exit" << std::endl;
		bool keppAlive = true;
		std::chrono::milliseconds dura(20);
		while (keppAlive){
			std::string command;
			if (serverAbyssPtr != nullptr){
				
				std::cin >> command;
				if (strcmp(command.c_str(), "exit") == 0){
					this->serverAbyssPtr->terminate();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}
				
			}
			std::this_thread::yield();
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
		method->execute(pc,rv);
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

	std::thread& XMLRPCpp_StartUp::execute(Server& server){
		
		Impl_->controllThread = std::thread(&XMLRPCpp_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPCpp_StartUp::run, this, server);
		return Impl_->thrd;
		
	}
	
	void XMLRPCpp_StartUp::run(Server& server){
		
		try {
			XmlRpc::XmlRpcServer s;
			FunctionRepository* fr = server.getRepository();
			
			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				XMLRPC_Method* b = new XMLRPC_Method(it->second, it->first, &s);
					s.addMethod(b);
			}
			
			s.bindAndListen(8081);
			s.enableIntrospection(true);
			xmlServerPnt = &s;
			//TODO: Figure out what that means
			s.work(-1.0);
		}
		catch (std::exception const& e) {
			std::cerr << "Something failed.  " << e.what() << std::endl;
		}
		
	}
	void XMLRPCpp_StartUp::controll(){
		
		std::cout << "Type \"exit\" to exit" << std::endl;
		
		bool keppAlive = true;
		std::chrono::milliseconds dura(20);
		while (keppAlive){
			std::string command;
			if (xmlServerPnt != nullptr){

				std::cin >> command;
				if (strcmp(command.c_str(), "exit") == 0){
					this->xmlServerPnt->shutdown();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}
		

	}

	
}