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

#include "requesthandler.h"
#include "mime_types.hpp"
#include <boost/lexical_cast.hpp>
#include <thread>
#include <chrono>
#include "pugixml.hpp"
#include <iostream>
#include <algorithm>

namespace serpents{
	namespace http{
		namespace server2{
			namespace util{
				namespace xml{
					void toLower(std::string&s){
						std::transform(s.begin(), s.end(), s.begin(), ::tolower);
					}
					class IXMLClass{
					public:
						virtual void getXMLParameters(std::string& xmlDoc, std::string& functionName, ParameterContainer& pc) = 0;
						template< typename T>
						T& generateXMLResponse(T& responseDoc, ParameterContainer& response){
							PugiXML* pugi = new PugiXML;
							pugi->generateXMLResponse(responseDoc, response);
							delete pugi;
							return responseDoc;
						}
					};

					class PugiXML : public IXMLClass{
						void getXMLParameters(std::string& xmlDoc, std::string& functionName, ParameterContainer& pc){
							bool foundParams = false;
							pugi::xml_document doc;
							pugi::parse_wconv_attribute;

							pugi::xml_parse_result result = doc.load(xmlDoc.c_str(), xmlDoc.size());
							if (!result){
								throw std::exception("unable to read xml doc");
							}
							pugi::xml_node root = doc.child("methodCall");
							functionName = root.child_value("methodName");
							if (functionName.compare("") == 0){
								throw std::exception("no method name detected");
							}
							pugi::xml_node params = root.child("params");

							for each(pugi::xml_node param in params.children())
							{

								pugi::xml_node value = param.first_child();
								std::string nodeWithCorectStructure = value.first_child().child_value();
								std::string nodeWithoutCorectStructure = value.child_value();
								if (nodeWithCorectStructure.compare("") == 0){
									pc.add(nodeWithoutCorectStructure);
								}
								else{
									std::string name = value.first_child().name();
									toLower(name);
									if (name.compare("i4") == 0 || name.compare("int") == 0){
										pc.add(boost::lexical_cast<int>(nodeWithCorectStructure));
										foundParams = true;
									}
									if (name.compare("double") == 0){
										pc.add(boost::lexical_cast<double>(nodeWithCorectStructure));
										foundParams = true;
									}
									if (name.compare("boolean") == 0){
										pc.add(boost::lexical_cast<bool>(nodeWithCorectStructure));
										foundParams = true;
									}
									if (name.compare("string") == 0){
										pc.add(nodeWithCorectStructure);
										foundParams = true;
									}
								}
							}
							if (!foundParams){
								throw(std::exception("No supported variable types found"));
							}
						}// getXMLParameters
					public:
						pugi::xml_document& generateXMLResponse(pugi::xml_document& responseDoc, ParameterContainer& response){
							pugi::xml_node root = responseDoc.append_child("methodResponse");
							pugi::xml_node params = root.append_child("params");
							auto it = response.getAll().begin();
							for (unsigned int i = 0; i < response.size(); ++i)
							{
								pugi::xml_node param = params.append_child("param");
								pugi::xml_node value = param.append_child("value");
								pugi::xml_node child = value.append_child(response.getType(i).c_str());
								child.text().set(response.getString(i).c_str());
							}

							return responseDoc;
						} // generateXMLResponse
					};



				}

			} //util


			void RequestHandler::handleRequest(request& req, reply& rep, ServerFunctionRepository& functionRepo){

				rep.status = reply::status_type::ok;

				ParameterContainer pc;
				std::string funcname;
				util::xml::IXMLClass* xmlutil = new util::xml::PugiXML;
				xmlutil->getXMLParameters(req.content, funcname, pc);

				sptr_method method = functionRepo.lookUpMethod(funcname);

				ParameterContainer result;
				method->execute(&pc, &result);

				pugi::xml_document responseDoc;
				xmlutil->generateXMLResponse(responseDoc, result);
				std::stringstream ss;
				responseDoc.print(ss);
				responseDoc.print(std::cout);
				rep.setContent(ss.str());
				rep.getHeaders().resize(2);
				rep.getHeaders()[0].name = "Content-Length";
				rep.getHeaders()[0].value = (boost::lexical_cast<std::string>(rep.getContent().size()));
				rep.getHeaders()[1].name = ("Content-Type");
				rep.getHeaders()[1].value = ("application/xml");

			}



		}
	}
} // namespace serpents