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
	protected:
		class Impl;
		Impl* Impl_;
	public: 
		Method();
		~Method();
		std::string getSignature();
		std::string getHelp();
		void setSignature(std::string sig);
		void setHelp(std::string help);
		void setName(std::string name);
		std::string Method::getName();
		virtual void execute(ParameterContainer* parameters, RetValue* rv) = 0;
		Method& operator=(Method& m);
		Method(const Method& m);
	};
	class Method::Impl{
		friend Method;
		std::string signature;
		std::string help;
		std::string name;
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
		FunctionRepository& operator=(FunctionRepository& fr);
		FunctionRepository(FunctionRepository& fr);
		Impl* getImpl();
		~FunctionRepository();
		
	};
	class FunctionRepository::Impl{
	public:
		friend FunctionRepository;
		methodMap methodContainer;

	};
	
}


#endif