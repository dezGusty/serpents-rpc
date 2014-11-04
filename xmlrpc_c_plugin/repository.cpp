#include "serpents\rpc\server\repository.h"


namespace serpents{
	
	void FunctionRepository::addMethod(Method* method){
		std::string name = method->getName();
		if (!name.empty()){
			Impl_->methodContainer.insert(std::pair<std::string, Method*>(name, method));
		}
		else{
			throw(std::exception("no name found for method"));
		}
	}

	
	FunctionRepository::FunctionRepository(){
		Impl_ = new Impl;
	}

	FunctionRepository& FunctionRepository::operator=(FunctionRepository& fr){
		if (this != &fr){
			for each (auto var in fr.Impl_->methodContainer)
			{
				this->Impl_ = new Impl;
				Impl_->methodContainer.insert(std::pair<std::string, Method*>(var.first, var.second));
			}
			return *this;
		}
		else{
			return fr;
		}

	}
	FunctionRepository::FunctionRepository(FunctionRepository& fr){
		for each (auto var in fr.Impl_->methodContainer)
		{
			this->Impl_ = new Impl;
			this->Impl_->methodContainer.insert(std::pair<std::string, Method*>(var.first, &(*var.second)));
		}
	}
	FunctionRepository::~FunctionRepository(){
		delete Impl_;
	}
	FunctionRepository::Impl* FunctionRepository::getImpl(){
		if (Impl_ == nullptr){
			throw(std::exception("no function repository set"));
		}
		return Impl_;
	}

}