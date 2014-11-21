#ifndef XMLUIL_H_
#define XMLUIL_H_
#pragma once 
//boost libs 
#include "boost\lexical_cast.hpp"

// system libs 
#include <string>
#include <algorithm>
#include <iostream>
//pugixml 
#define PUGIXML_HEADER_ONLY
#include "pugixml/pugixml.hpp"
// project libs
#include "serpents-rpc\serpents\rpc\parameters\parametercontainer.hpp"
#include "serpents-ssl\base.h"
#include <iostream>
namespace serpents{
	namespace util{
		namespace xml{
					
					class IXMLClass{
					public:
						
						virtual void getXMLParameters(std::string& xmlDoc, std::string& functionName, serpents::ParameterContainer& pc) = 0;
						
						virtual std::string generateXMLDoc(std::string& methodName, serpents::ParameterContainer* pc, std::string& result) = 0;
						
						virtual void getResponseParameters(std::string& xmlDoc, serpents::ParameterContainer& pc) = 0;

						template< typename T>
						T& generateXMLResponse(T& responseDoc, serpents::ParameterContainer& response){
							PugiXML* pugi = new PugiXML;
							pugi->generateXMLResponse(responseDoc, response);
							delete pugi;
							return responseDoc;
						}
						void toLower(std::string&s){
							std::transform(s.begin(), s.end(), s.begin(), ::tolower);
						}
					};

					class PugiXML : public IXMLClass{
						void getXMLParameters(std::string& xmlDoc, std::string& functionName, serpents::ParameterContainer& pc){
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
									if (name.compare("boolean") == 0 || name.compare("bool") == 0){
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
							//	throw(std::exception("No supported variable types found"));
							}
						}// getXMLParameters

						
					public:
						void getResponseParameters(std::string& xmlDoc, serpents::ParameterContainer& pc){
							bool foundParams = false;
							pugi::xml_document* doc = new pugi::xml_document;
							pugi::parse_wconv_attribute;
							pugi::parse_default;
							pugi::parse_comments;
						
							pugi::xml_parse_result result = doc->load(xmlDoc.c_str(), xmlDoc.size());

							if (!result){
								throw std::exception("unable to read xml doc");
							}
							pugi::xml_node root = doc->child("methodResponse");
							pugi::xml_node params = root.child("params");

							for each(pugi::xml_node param in params.children())
							{
							//	pugi::xml_node var = param.child("value");
							//	for (var; var; var = param.next_sibling("value"))
							//	{
							//		std::string nodeWithCorectStructure = var.first_child().child_value();
							//	}
								pugi::xml_node value = param.first_child();
								std::string nodeWithCorectStructure = value.first_child().child_value();

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
								if (name.compare("boolean") == 0 || name.compare("bool")==0){
									pc.add(boost::lexical_cast<bool>(nodeWithCorectStructure));
									foundParams = true;
								}
								if (name.compare("string") == 0){
									pc.add(nodeWithCorectStructure);
									foundParams = true;
								}
							}
							delete doc;
							if (!foundParams){
								throw(std::exception("No supported variable types found"));
							}

						}
						pugi::xml_document& generateXMLResponse(pugi::xml_document& responseDoc, serpents::ParameterContainer& response){
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
							//responseDoc.print(std::cout);
							return responseDoc;
						} // generateXMLResponse
						std::string generateXMLDoc(std::string& methodName, serpents::ParameterContainer* pc, std::string& result){
							pugi::xml_document xmlDoc;
							pugi::xml_node root = xmlDoc.append_child("methodCall");
							pugi::xml_node mName = root.append_child("methodName");
							mName.text().set(methodName.c_str());
							pugi::xml_node params = root.append_child("params");
							auto it = pc->getAll().begin();
							for (unsigned int i = 0; i < pc->size(); ++i)
							{
								pugi::xml_node param = params.append_child("param");
								pugi::xml_node value = param.append_child("value");
								pugi::xml_node child = value.append_child(pc->getType(i).c_str());
								child.append_child(pugi::node_pcdata).set_value(pc->getString(i).c_str());
								//child.text().set(pc->getString(i).c_str());
							}
							std::stringstream ss;
							xmlDoc.save(ss, "  ", pugi::format_raw );
							
							return ss.str();
						}
					};

				} //xml

			} //util
} //serpents

#endif // XMLUIL_H_