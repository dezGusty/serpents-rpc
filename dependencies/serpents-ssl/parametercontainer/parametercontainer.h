#pragma once
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
#include <sstream>
#include "base.h"
namespace serpents{
	namespace param{
			class SSL_SERVER_API ParamContainerException : public std::exception{
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

			class SSL_SERVER_API ParameterContainer{
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
					double get_double() const { return DOUBLE; }
					bool get_bool() const { return BOOL; }
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
					std::vector<bool> boolVec;
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
							case any::Double:   Impl_->doubleVec.push_back(vec[i].get_double());
								Impl_->allVec.push_back(std::to_string(vec[i].get_double()));
								Impl_->typeVec.push_back(type::Double);
								break;
							case any::String:   Impl_->stringVec.push_back(vec[i].get_string());
								Impl_->allVec.push_back(vec[i].get_string());
								Impl_->typeVec.push_back(type::String);
								break;
							case any::Bool:   Impl_->boolVec.push_back(vec[i].get_bool());
								std::stringstream converter;
								converter << vec[i].get_bool();
								Impl_->allVec.push_back(converter.str());
								Impl_->typeVec.push_back(type::Bool);
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
				ParameterContainer(const ParameterContainer& pc);
				ParameterContainer& operator=(ParameterContainer& pc);
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
				~ParameterContainer();
				std::vector<int>& getInts();
				std::vector<double>& getDoubles();
				std::vector<std::string>& getStrings();
				std::vector<std::string>& getAll();
				int getInt(unsigned int n);
				double getDouble(unsigned int n);
				std::string getString(unsigned int n);
				bool getBool(unsigned int n);
				unsigned int size();
				std::string getType(unsigned int n);
				void push(std::string s);
				std::string pop();
			};
	} //namespace parameter
} //namespace serpents 

#endif