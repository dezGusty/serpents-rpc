#pragma once
#ifndef PARAMETER_CON_H
#define PARAMETER_CON_H

#include "any.h"
#include "base.h"
#include <vector>
#include <string>
#include <exception>
#ifdef SERPENTSRPC_EXPORTS

#define PARAMETERDLL _declspec(dllexport)
#else
#define PARAMETERDLL _declspec(dllimport)
#endif

namespace serpents{
	class PARAMETERDLL ParamContainerException : public std::exception{
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
	
	class PARAMETERDLL ParameterContainer{
	public:
		enum type { Int, Float, Double, String, Bool };
	private:
		struct any{
			enum type { Int, Float, Double, String, Bool };

			explicit any(int   e) : INT(e), m_type(Int) {}
			explicit any(float e) :FLOAT(e), m_type(Float){ }
			explicit any(std::string e): STRING(e), m_type(String){ }
			explicit any(double e) : DOUBLE(e), m_type(Double){ }
			explicit any(bool e) : BOOL(e), m_type(Bool){}
			type get_type() const { return m_type; }
			int get_int() const { return INT; }
			float get_float() const { return FLOAT; }
			std::string get_string() const { return STRING; }
		private:
			type m_type;
			int   INT =0;
			float FLOAT =0;
			double DOUBLE =0;
			bool BOOL =0;
			std::string STRING ="";
			
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
					case any::Int:	   Impl_->intVec.push_back(vec[i].get_int());
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
				
				throw(ParameterContainer(std::string("problem adding ")+e.what()));
			}
		}
	public:
		template <class ...Args>
		ParameterContainer(Args... args){
			Impl_ = new Impl;
			parse(any(args)...);
		}
		ParameterContainer(const ParameterContainer& pc);
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
		unsigned int size();
		std::string getType(unsigned int n);
		void push(std::string s);
		std::string pop();
	};	

}

#endif