#ifndef PARAMETER_CON_H
#define PARAMER_CON_H


#define PARAMETER_CON_EXPORT
#ifdef PARAMETER_CON_EXPORT
#define PARAMETERDLL _declspec(dllexport)
#else
#define PARAMETERDLL _declspec(dllimport)
#endif
#include <vector>
#include <iostream>
#include "any.h"
#include <exception>

namespace serpents{
	class ParamContainerException : public std::exception{
		std::string description;
	public:
		ParamContainerException(std::string d) : description(d){}
		friend std::ostream& operator<<(std::ostream& is, ParamContainerException e){
			is << e.description;
			return is;
		}

	};
	class ParameterContainer{
		enum type { Int, Float, Double, String, Bool };
		std::vector<type> typeVec;
		std::vector<int> intVec;
		std::vector<double> doubleVec;
		std::vector<std::string> stringVec;
		std::vector<std::string> allVec;
		
		template <class ...Args>
		void parse(const Args&... args)
		{
			std::vector<any> vec = { args... };
			for (unsigned i = 0; i < vec.size(); ++i) {
				switch (vec[i].get_type()) {
				case any::Int:	    intVec.push_back(vec[i].get_int());
					allVec.push_back(std::to_string(vec[i].get_int()));
					typeVec.push_back(type::Int);
					break;
				case any::Float:    doubleVec.push_back(vec[i].get_float());
					allVec.push_back(std::to_string(vec[i].get_float()));
					typeVec.push_back(type::Float);
					break;
				case any::String:   stringVec.push_back(vec[i].get_string());
					allVec.push_back(vec[i].get_string());
					typeVec.push_back(type::String);
					break;
				}
			}
		}

	public:
		template <class ...Args>
		ParameterContainer(Args... args){
			parse(any(args)...);
		}
		ParameterContainer(const ParameterContainer& pc){
			for each (int var in pc.intVec)
			{
				this->intVec.push_back(var);
			}
			for each (double var in pc.doubleVec)
			{
				this->doubleVec.push_back(var);
			}
			for each (std::string var in pc.stringVec)
			{
				this->stringVec.push_back(var);
			}
			for each (std::string var in pc.allVec)
			{
				this->allVec.push_back(var);
			}
		}
		template <class ...Args>
		void add(Args... args)
		{
			parse(any(args)...);
		}
		std::vector<int>& getInts(){
			return intVec;
		}

		std::vector<double>& getDoubles(){
			return doubleVec;
		}
		std::vector<std::string>& getStrings(){
			return stringVec;
		}
		int getInt(unsigned int n){
			if (n < 0 || n > allVec.size())
				throw(ParamContainerException("out of bounds exception"));
			try{
				return std::stoi(allVec.at(n));
			}
			catch (std::exception e){

				throw(ParamContainerException("invalid num"));

			}
		}
		double getDouble(unsigned int n){
			try{
				if (n < 0 || n > allVec.size())
					throw(ParamContainerException("out of bounds exception"));
				return std::stod(allVec.at(n));
			}
			catch (std::exception e){
				throw(ParamContainerException("invalid num"));
			}
		}
		std::string getString(unsigned int n){
			try{
				if (n < 0 || n > allVec.size())
					throw(ParamContainerException("out of bounds exception"));
				return allVec.at(n);
			}
			catch (std::exception e){
				throw(ParamContainerException("no string found"));
			}
		}

		unsigned int size(){
			return allVec.size();
		}
		std::string getType(unsigned int n){
			if (n > 0 || n > typeVec.size()){
				int t = typeVec.at(n);
				switch (t){
				case type::Int:  return "Int"; break;
				case type::Double:return "Double"; break;
				case type::Bool: return "Bool"; break;
				case type::Float: return "Float"; break;
				case type::String: return "String";  break;

				}
			}
		}
		void push(std::string s){
			allVec.push_back(s);
		}
		std::string pop(){
			if (allVec.size() >= 1){
				std::string s = allVec.at(allVec.size() - 1);
				allVec.pop_back();
				return s;
			}
			else{
				return "";
			}
		}
	};
}



#endif