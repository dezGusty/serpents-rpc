#include "stdafx.h"
#include "repository.h"
#include <iostream>
namespace serpents{
	Method::Method() {
	
		signature  = new std::string("?");
		help = new std::string( "no help availible");
	}
	void FunctionRepository::addMethod(const std::string& name, Method* method){
		Impl_->methodContainer.insert(std::pair<std::string, Method*>(name, method));
	}
	Method::~Method(){
		delete signature;
		delete help;
	}
	void FunctionRepository::executeAll(){
		
	}
	FunctionRepository::FunctionRepository(){
		Impl_ = new Impl;	}
	
	FunctionRepository& FunctionRepository::operator=(const FunctionRepository& fr){
		for each (std::pair<std::string,Method*> var in fr.Impl_->methodContainer)
		{
			Method* m = nullptr; 
			memset(m, 0, sizeof(var.second));
			memcpy(m, var.second, sizeof(var.second));
			this->Impl_->methodContainer.insert(std::pair<std::string, Method*>(var.first,m));
		}
		return *this;
	}
	
	FunctionRepository::~FunctionRepository(){
		methodMap::iterator it;
		for (it = Impl_->methodContainer.begin(); it != Impl_->methodContainer.end(); ++it){
			std::cout << "deleting obj" << std::endl;
			delete it->second;
		}
		delete Impl_;
	}


}