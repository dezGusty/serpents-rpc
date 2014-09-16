#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "base.h"
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "parametercontainer.h"
#include "retValue.h"
namespace serpents{
	
	class SERPENTSDLL Method{
	private:
		Method(const Method& m) = delete;
	public:
		std::string* signature;
		std::string* help;
	public: 
		Method();
		~Method();
	
		virtual void execute(ParameterContainer& parameters, RetValue& rv) = 0;
	};

	class SERPENTSDLL FunctionRepository{
	private:
		class  Impl;
		Impl* Impl_;
	public:
		FunctionRepository();
		typedef std::map<std::string, Method *> methodMap;
		void addMethod(const std::string& name,Method* method);
		void executeAll();
		FunctionRepository& operator=(const FunctionRepository& fr);
		Impl* getImpl(){
			return Impl_;
		}
		~FunctionRepository();
		
	};
	class FunctionRepository::Impl{
	public:
		friend FunctionRepository;
		methodMap methodContainer;

	};
	
}


#endif