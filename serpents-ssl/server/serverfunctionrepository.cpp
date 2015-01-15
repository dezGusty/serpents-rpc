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

#include "serverfunctionrepository.h"
#include <sstream>
namespace serpents{
  namespace http{
    namespace server2{
      class Serpents_SSL_RetValue::Impl{
        friend Serpents_SSL_RetValue;
        serpents::ParameterContainer cont;
      };
      Serpents_SSL_RetValue::Serpents_SSL_RetValue(){
        Impl_ = new Impl;
      }
      Serpents_SSL_RetValue::~Serpents_SSL_RetValue(){
        delete Impl_;
      }
      void Serpents_SSL_RetValue::setValue(int n){
        Impl_->cont.add(n);
      }
      void Serpents_SSL_RetValue::setValue(bool n){
        Impl_->cont.add(n);
      }
      void Serpents_SSL_RetValue::setValue(double n){
        Impl_->cont.add(n);
      }
      void Serpents_SSL_RetValue::setValue(std::string n){
        Impl_->cont.add(n);
      }
      void Serpents_SSL_RetValue::setValue(float f){
        Impl_->cont.add(f);
      }
      ParameterContainer& Serpents_SSL_RetValue::getRetValue(){
        return Impl_->cont;
      }
      class ServerMethod::Impl{
        friend ServerMethod;
        std::string signature_;
        std::string help_;
        std::string name_;
      };
      void ServerMethod::setSignature(std::string& signature){
        Impl_->signature_ = signature;
      }
      void ServerMethod::setHelp(std::string& help){
        Impl_->help_ = help;
      }
      void ServerMethod::setName(std::string& name){
        Impl_->name_ = name;
      }
      std::string ServerMethod::getSignature(){
        return Impl_->signature_;
      }
      std::string ServerMethod::getHelp(){
        return Impl_->help_;
      }
      std::string ServerMethod::getName(){
        return Impl_->name_;
      }

      ServerMethod::ServerMethod(std::string& name, std::string& help, std::string& signature){
        Impl_ = new Impl();
        this->setName(name);
        this->setHelp(help);
        this->setSignature(signature);
      }
      ServerMethod::ServerMethod(){
        Impl_ = new Impl();
      }
      ServerMethod::~ServerMethod(){
        delete Impl_;
      }


      // exception 
      RepoException::RepoException(std::string& errorMsg) : error(errorMsg){  }
      const char* RepoException::what() const noexcept{ return error.c_str; }

      //server function repo
      class ServerFunctionRepository::Impl{
        friend ServerFunctionRepository;
        std::map<std::string, sptr_method> map;
      };
      ServerFunctionRepository::ServerFunctionRepository(const ServerFunctionRepository& sfr){
        this->Impl_ = new Impl;
        for (auto it = sfr.Impl_->map.begin(); it != sfr.Impl_->map.end(); ++it){
          this->Impl_->map[it->first] = it->second;
        }
      }
      ServerFunctionRepository::ServerFunctionRepository(){
        Impl_ = new Impl;

      }

      ServerFunctionRepository::~ServerFunctionRepository(){
        delete Impl_;
      }

      void ServerFunctionRepository::addServerMethod(sptr_method& method){

        Impl_->map.insert(std::pair<std::string, sptr_method>((*method)->getName(), std::move(method)));

      }
      void ServerFunctionRepository::addServerMethod(serpents::Method* method){
        std::shared_ptr<serpents::Method*> smethod = std::make_shared<serpents::Method*>(method);
        //Impl_->map.insert(std::pair<std::string, sptr_method>(method->getName(), std::move(smethod)));

      }
      sptr_method ServerFunctionRepository::lookUpMethod(std::string& name){
        if (!Impl_->map.empty()){
          auto it = Impl_->map.find(name);
          if (it == Impl_->map.end()){
            std::stringstream ss;
            ss << "method " << "\"" << name << "\"" << " not present in server function repository";
            throw(RepoException(ss.str()));
          }
          else {
            return Impl_->map.find(name)->second;            
          }
        }
        else{
          throw(RepoException(std::string("function repository is empty")));
        }
      }
    } // namespace server2
  } // namespace http
}// namespace serpents