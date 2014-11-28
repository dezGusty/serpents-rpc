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
/*
//serpents libs
#include "serpents\rpc\parameters\parametercontainer.hpp"

namespace serpents{
  ParameterContainer::ParameterContainer(const ParameterContainer& pc){
      for each (int var in pc.Impl_->intVec)
      {
        this->Impl_->intVec.push_back(var);
      }
      for each (double var in pc.Impl_->doubleVec)
      {
        this->Impl_->doubleVec.push_back(var);
      }
      for each (std::string var in pc.Impl_->stringVec)
      {
        this->Impl_->stringVec.push_back(var);
      }
      for each (bool var in pc.Impl_->boolVec)
      {
        this->Impl_->boolVec.push_back(var);
      }
      for each (std::string var in pc.Impl_->allVec)
      {
        this->Impl_->allVec.push_back(var);
      }
      for each (ParameterContainer::type var in pc.Impl_->typeVec)
      {
        this->Impl_->typeVec.push_back(var);
      }
    }
    ParameterContainer& ParameterContainer::operator=(ParameterContainer& pc){
      for each (int var in pc.Impl_->intVec)
      {
        this->Impl_->intVec.push_back(var);
      }
      for each (double var in pc.Impl_->doubleVec)
      {
        this->Impl_->doubleVec.push_back(var);
      }
      for each (std::string var in pc.Impl_->stringVec)
      {
        this->Impl_->stringVec.push_back(var);
      }
      for each (bool var in pc.Impl_->boolVec)
      {
        this->Impl_->boolVec.push_back(var);
      }
      for each (std::string var in pc.Impl_->allVec)
      {
        this->Impl_->allVec.push_back(var);
      }
      for each (ParameterContainer::type var in pc.Impl_->typeVec)
      {
        this->Impl_->typeVec.push_back(var);
      }
      return *this;
    }

    std::vector<int>& ParameterContainer::getInts(){
      return Impl_->intVec;
    }

    std::vector<double>& ParameterContainer::getDoubles(){
      return Impl_->doubleVec;
    }
    std::vector<std::string>& ParameterContainer::getStrings(){
      return Impl_->stringVec;
    }
    int ParameterContainer::getInt(unsigned int n){
      if (n < 0 || n > Impl_->allVec.size())
        throw(ParamContainerException("out of bounds exception"));
      try{
        return std::stoi(Impl_->allVec.at(n));
      }
      catch (std::exception& e){

        throw(ParamContainerException(std::string("invalid num") + e.what()));

      }
    }
    double ParameterContainer::getDouble(unsigned int n){
      try{
        if (n < 0 || n >Impl_->allVec.size())
          throw(ParamContainerException("out of bounds exception"));
        return std::stod(Impl_->allVec.at(n));
      }
      catch (std::exception& e){
        throw(ParamContainerException(std::string("invalid num") + e.what()));
      }
    }
    std::string ParameterContainer::getString(unsigned int n){
      try{
        if (n < 0 || n > Impl_->allVec.size())
          throw(ParamContainerException("out of bounds exception"));
        return Impl_->allVec.at(n);
      }
      catch (std::exception& e){
        throw(ParamContainerException(std::string("no string found", e.what())));
      }
    }
    bool ParameterContainer::getBool(unsigned int n){
      try{
        if (n < 0 || n >Impl_->allVec.size())
          throw(ParamContainerException("out of bounds exception"));
        return static_cast<bool>(std::stoi(Impl_->allVec.at(n)));
      }
      catch (std::exception& e){
        throw(ParamContainerException(std::string("invalid num") + e.what()));
      }
    }

    unsigned int ParameterContainer::size(){
      return Impl_->allVec.size();
    }
    std::string ParameterContainer::getType(unsigned int n){
      if (n > Impl_->typeVec.size()){
        throw(ParamContainerException("no string found"));
      }
      int t = Impl_->typeVec.at(n);
      switch (t){
      case type::Int:  return "int"; break;
      case type::Double:return "double"; break;
      case type::Bool: return "boolean"; break;
      case type::Float: return "float"; break;
      case type::String: return "string";  break;
      }
      throw(ParamContainerException("type not supported"));
    }
    void ParameterContainer::push(std::string s){
      Impl_->allVec.push_back(s);
    }
    std::string ParameterContainer::pop(){
      if (Impl_->allVec.size() >= 1){
        std::string s = Impl_->allVec.at(Impl_->allVec.size() - 1);
        Impl_->allVec.pop_back();
        return s;
      }
      else{
        return "";
      }
    }
    std::vector<std::string>& ParameterContainer::getAll(){
      return Impl_->allVec;
    }
    ParameterContainer::~ParameterContainer(){
      delete Impl_;
    }
  
}// serpents 
*/