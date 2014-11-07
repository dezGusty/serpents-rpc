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



#ifndef SERVER_FUNCTION_REPOSITORY_H_
#define SERVER_FUNCTION_REPOSITORY_H_
#include <map>
#include <memory>
#include "serpents-rpc\serpents\rpc\parameters\parametercontainer.hpp"
#include "serpents-rpc\serpents\rpc\parameters\retValue.h"

#include <thread>
#include <chrono>
#include <fstream>
#include "serpents-ssl\base.h"
#include "serpents-rpc\serpents\rpc\server\method.hpp"
//TODO: change ServerMethod  and FunctionRepository to the serpents-rpc immplementations

namespace serpents{
	namespace http{
		namespace server2{
			class Serpents_SSL_RetValue :public RetValue{
				class Impl;
				Impl* Impl_;
			public: 
				Serpents_SSL_RetValue();
				~Serpents_SSL_RetValue();
				void setValue(int n) override;
				void setValue(double n) override;
				void setValue(bool b) override;
				void setValue(std::string s)override;
				ParameterContainer& getRetValue();
			};

			class SSL_SERVER_API ServerMethod{
			private:
				class Impl;
				Impl* Impl_;
			public:
				virtual void execute(serpents::ParameterContainer* pc, Serpents_SSL_RetValue* result) = 0;
				ServerMethod(std::string& name, std::string& help, std::string& signature);
				ServerMethod();
				~ServerMethod();
				void setSignature(std::string& signature);
				void setHelp(std::string& help);
				void setName(std::string& name);
				std::string getSignature();
				std::string getHelp();
				std::string getName();
			};
	
			typedef std::shared_ptr<serpents::Method*> sptr_method;
			typedef std::map<std::string, sptr_method> repository_map;

			//server function repo
			class SSL_SERVER_API ServerFunctionRepository{
			private:
				class Impl;
				Impl* Impl_;
			public:

				ServerFunctionRepository();
				~ServerFunctionRepository();
				void ServerFunctionRepository::addServerMethod(serpents::Method* method);
				void ServerFunctionRepository::addServerMethod(sptr_method& method);
				sptr_method lookUpMethod(std::string& name);

			};
			
			class RepoException : public std::exception{
				std::string error;
			public:
				RepoException(std::string& errorMsg) ;
				std::string what();
			};
		}
	}
} // namespace serpents
#endif // SERVER_FUNCTION_REPOSITORY_H_