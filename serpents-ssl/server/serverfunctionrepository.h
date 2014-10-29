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
#include "parametercontainer\parametercontainer.h"

#include <thread>
#include <chrono>
#include <fstream>
#include "base.h"
namespace serpents{
	namespace http{
		namespace server2{

			class SSL_SERVER_API ServerMethod{
			private:
				class Impl;
				Impl* Impl_;
			public:
				virtual void execute(serpents::param::ParameterContainer* pc, serpents::param::ParameterContainer* result) = 0;
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
			class ServerMethod::Impl{
				friend ServerMethod;
				std::string signature_;
				std::string help_;
				std::string name_;
			};
			class SampleMethod : public ServerMethod{
			public:
				SampleMethod(std::string& name, std::string& help, std::string& signature) {
					setName(name);
					setHelp(help);
					setSignature(signature);

				}
				SampleMethod(){}
				void execute(serpents::param::ParameterContainer* pc, serpents::param::ParameterContainer* result){
					//result->add(pc->getInt(0) + pc->getInt(1));
					std::chrono::milliseconds dura(5000);
					std::this_thread::sleep_for(dura);
					result->add(pc->getInt(0) + pc->getDouble(1));

				}
			};
			class EchoMethod : public ServerMethod{
			public:
				void execute(serpents::param::ParameterContainer* pc, serpents::param::ParameterContainer* result){
					*result = *pc;
				}
			};

			class WriteToFile : public ServerMethod{
			public:
				void execute(serpents::param::ParameterContainer* pc, serpents::param::ParameterContainer* result){
					std::string fileName = pc->getString(0);
					std::ofstream outfile(fileName, std::ofstream::binary);
					std::string s("opened");
					outfile.write(s.c_str(), s.length());
					std::chrono::milliseconds dura(2000);
					std::this_thread::sleep_for(dura);
					outfile.close();

					std::ifstream is(fileName.c_str());
					result->add(is.good());

				}
			};

			typedef std::shared_ptr<ServerMethod> sptr_method;
			typedef std::map<std::string, sptr_method> repository_map;

			//server function repo
			class SSL_SERVER_API ServerFunctionRepository{
			private:
				class Impl;
				Impl* Impl_;
			public:

				ServerFunctionRepository();
				~ServerFunctionRepository();
				void addServerMethod(std::shared_ptr<ServerMethod>& method);
				sptr_method lookUpMethod(std::string& name);

			};
			class ServerFunctionRepository::Impl{
				friend ServerFunctionRepository;
				std::map<std::string, std::shared_ptr<ServerMethod>> map;
			};
			class RepoException : public std::exception{
				std::string error;
			public:
				RepoException(std::string& errorMsg) : error(errorMsg){	}
				std::string what(){ return error; }
			};
		}
	}
} // namespace serpents

#endif // SERVER_FUNCTION_REPOSITORY_H_