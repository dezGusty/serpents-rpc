#pragma once

/*
#ifndef PARAMETER_CON_H
#define PARAMETER_CON_H

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

//serpents libs 


//c++ system libs
#include <vector>
#include <string>
#include <exception>

namespace serpents{
	class  ParamContainerException : public std::exception{
		class Impl{ friend ParamContainerException;  std::string description; };
		Impl* Impl_;

	public:
		ParamContainerException(std::string d)  { Impl_ = new Impl; Impl_->description = d; }
		std::string getDescription(){ return Impl_->description; }
		friend std::ostream& operator<<(std::ostream& is, ParamContainerException e){
			is << e.getDescription();
			return is;
		}
		~ParamContainerException(){
			delete Impl_;
		}

	};

	class ParameterContainer{
	public:
		enum type { Int, Float, Double, String, Bool };
	private:
		struct any{
			enum type { Int, Float, Double, String, Bool };

			explicit any(int   e) : INT(e), m_type(Int) {}
			explicit any(float e) :FLOAT(e), m_type(Float){ }
			explicit any(std::string e) : STRING(e), m_type(String){ }
			explicit any(double e) : DOUBLE(e), m_type(Double){ }
			explicit any(bool e) : BOOL(e), m_type(Bool){}
			type get_type() const { return m_type; }
			int get_int() const { return INT; }
			float get_float() const { return FLOAT; }
			std::string get_string() const { return STRING; }
		private:
			type m_type;
			int   INT = 0;
			float FLOAT = 0;
			double DOUBLE = 0;
			bool BOOL = 0;
			std::string STRING = "";

		};

		class Impl{
			friend ParameterContainer;

			std::vector<type> typeVec;
			std::vector<int> intVec;
			std::vector<double> doubleVec;
			std::vector<std::string> stringVec;
			std::vector<std::string> allVec;
		};
		Impl* Impl_;


		template <class ...Args>
		void parse(const Args&... args)
		{
			try{
				std::vector<any> vec = { args... };
				for (unsigned i = 0; i < vec.size(); ++i) {
					switch (vec[i].get_type()) {
					case any::Int:     Impl_->intVec.push_back(vec[i].get_int());
						Impl_->allVec.push_back(std::to_string(vec[i].get_int()));
						Impl_->typeVec.push_back(type::Int);
						break;
					case any::Float:   Impl_->doubleVec.push_back(vec[i].get_float());
						Impl_->allVec.push_back(std::to_string(vec[i].get_float()));
						Impl_->typeVec.push_back(type::Float);
						break;
					case any::String:   Impl_->stringVec.push_back(vec[i].get_string());
						Impl_->allVec.push_back(vec[i].get_string());
						Impl_->typeVec.push_back(type::String);
						break;
					}
				}
			}
			catch (std::exception& e){

				throw(ParameterContainer(std::string("problem adding ") + e.what()));
			}
		}
	public:
		template <class ...Args>
		ParameterContainer(Args... args){
			Impl_ = new Impl;
			parse(any(args)...);
		}
		template <class ...Args>
		void add(Args... args)
		{
			try{
				parse(any(args)...);
			}
			catch (std::exception& e){
				throw(ParameterContainer(std::string("problem adding ") + e.what()));
			}
		}
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
			for each (std::string var in pc.Impl_->allVec)
			{
				this->Impl_->allVec.push_back(var);
			}
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

		unsigned int ParameterContainer::size(){
			return Impl_->allVec.size();
		}
		std::string ParameterContainer::getType(unsigned int n){
			if (n > Impl_->typeVec.size()){
				throw(ParamContainerException("no string found"));
			}
			int t = Impl_->typeVec.at(n);
			switch (t){
			case type::Int:  return "Int"; break;
			case type::Double:return "Double"; break;
			case type::Bool: return "Bool"; break;
			case type::Float: return "Float"; break;
			case type::String: return "String";  break;
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
	};
}

namespace serpents{


}
*/
#endif