//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#include "stdafx.h"
#include "repository.h"
#include <iostream>
namespace serpents{
	Method::Method() {
		Impl_ = new Impl;
		Impl_->signature = std::string("?");
		Impl_->help =std::string("no help availible");
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
	void FunctionRepository::addMethod(Method* method){
		std::string name = method->getName();
		if (!name.empty()){
			Impl_->methodContainer.insert(std::pair<std::string, Method*>(name, method));
		}
		else{
			throw(std::exception("no name found for method"));
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
	void FunctionRepository::executeAll(){
		
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
			this->Impl_->methodContainer.insert(std::pair<std::string, Method*>(var.first,&(*var.second)));
		}
	}
	FunctionRepository::~FunctionRepository(){
		delete Impl_;
	}
	FunctionRepository::Impl* FunctionRepository::getImpl(){
		return Impl_;
	}

}