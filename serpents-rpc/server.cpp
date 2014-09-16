#include "stdafx.h"
#include "server.h"

namespace serpents{
	
	Server::Server() { 
		Impl_ = new Impl();
		this->Impl_->port = 8081;
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
	FunctionRepository* Server::getRepository(){
		return this->repository;
	}
}