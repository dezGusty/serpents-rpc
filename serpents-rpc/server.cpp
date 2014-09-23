#include "stdafx.h"
#include "server.h"

namespace serpents{
	
	Server::Server() { 
		Impl_ = new Impl();
		Impl_->soPtr = new XMLRPC_CServerOptions;
		Impl_->socppPtr = new XMLRPCPP_ServerOptions;
		
	}
	Server::Server(unsigned int port){
		Impl_ = new Impl();
		this->Impl_->port = port;
	}
	std::string Server::getURI(){
		return this->Impl_->URI;
	}
	

	unsigned int Server::getPort(){
		return this->Impl_->port;
	}
	void Server::setURI(std::string URI){
		this->Impl_->URI = URI;
	}
	void Server::setPort(unsigned port){
		this->Impl_->port = port;
	}
	void Server::run(){
		this->repository->executeAll();
	}
	void Server::setRepository(FunctionRepository& fr){
		this->repository = &fr;
	}
	void Server::addLogTarget(std::string type, std::string fileName){
		Impl_->logmap.insert(std::pair<std::string, std::string>(fileName, type));
	}
	std::map<std::string, std::string>* Server::getLogTargets(){
		return &Impl_->logmap;
	}
	FunctionRepository* Server::getRepository(){
		return this->repository;
	}

	XMLRPC_CServerOptions* Server::getXMLRPC_CServerOptions(){
		if (Impl_->soPtr == nullptr)
			throw std::exception("server options is a null pointer");
		return this->Impl_->soPtr; 
	}
	XMLRPCPP_ServerOptions* Server::getXMLRPCPP_ServerOptions(){
		return this->Impl_->socppPtr;
	}

}