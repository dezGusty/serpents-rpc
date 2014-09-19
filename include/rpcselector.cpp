#include "stdafx.h"
#include "RPCSelector.h"

namespace serpents{
	class ServerStartUp;
	//choose impl of server 
	void RPCSelector::selectRPCMethod(Server& server, std::string method){
		server_ = &server;
		//ServerStartUp* startUp =nullptr;
		if (strcmp(method.c_str(), "xmlrpc_c") == 0){
			ServerStartUpImpl_ = new XMLRPC_C_StartUp();
			
		}
		if (strcmp(method.c_str(), "xmlrpc++") == 0){

			ServerStartUpImpl_ = new XMLRPCpp_StartUp();
		}

	}
	void RPCSelector::stopServer(){
		assert(ss != nullptr);
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