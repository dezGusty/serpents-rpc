#include "stdafx.h"
#include "RPCSelector.h"

namespace serpents{
	class ServerStartUp;
	//choose impl of server 
	void RPCSelector::selectRPCMethod(Server& server, std::string method){
		server_ = &server;
		if (strcmp(method.c_str(), "xmlrpc_c") == 0){
			ServerStartUpImpl_ = new XMLRPC_C_StartUp();
			
		}
		if (strcmp(method.c_str(), "xmlrpc++") == 0){

			ServerStartUpImpl_ = new XMLRPCpp_StartUp();
		}
#ifdef USE_LOG4CPP
		auto map = server.getLogTargets();
		for (auto it = map->begin(); it != map->end(); ++it){
			Logger::getInstance().addAppender(it->second,it->first);
		}
		Logger::getInstance().info("---using library "+ method+"---");
#endif

	}
	void RPCSelector::stopServer(){
		ServerStartUpImpl_->runCon = false;
	}

	void RPCSelector::startServer(){
		ServerStartUpImpl_->execute(*server_);
		ServerStartUpImpl_->start();
	}
	RPCSelector::RPCSelector()
	{
	}


	RPCSelector::~RPCSelector()
	{
		delete ServerStartUpImpl_;
		
	}


	

	


}