#include "serpents\rpc\server\method.hpp"

namespace serpents{
	class Method::Impl{
		friend Method;
		std::string signature;
		std::string help;
		std::string name;
	};
	Method::Method() {
		Impl_ = new Impl;
		Impl_->signature = std::string("?");
		Impl_->help = std::string("no help availible");
	}
	Method& Method::operator=(Method& m){
		if (this != &m){
			this->Impl_ = new Impl;
			this->Impl_->help = std::string(Impl_->help);
			this->Impl_->signature = std::string(Impl_->signature);
			return *this;
		}
		else{
			return m;
		}
	}
	Method::~Method(){
		delete Impl_;
	}
	std::string Method::getSignature(){
		return Impl_->signature;
	}
	std::string Method::getHelp(){
		return Impl_->help;
	}
	void Method::setSignature(std::string sig){
		Impl_->signature = sig;
	}
	void Method::setHelp(std::string help){
		Impl_->help = help;
	}
	Method::Method(const Method& m){
		this->Impl_ = new Impl;
		Impl_->help = m.Impl_->help;
		Impl_->signature = m.Impl_->signature;
	}
	void Method::setName(std::string name){
		Impl_->name = name;
	}
	std::string Method::getName(){
		return Impl_->name;
	}
}