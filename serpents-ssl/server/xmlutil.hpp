#ifndef XMLUIL_H_
#define XMLUIL_H_
//boost libs 
#include "boost\lexical_cast.hpp"

// system libs 
#include <string>
#include <algorithm>
//pugixml 
#include "pugixml.hpp"
// project libs
#include "parametercontainer\parametercontainer.h"
namespace serpents{
	namespace util{
		namespace xml{
					void toLower(std::string&s){
						std::transform(s.begin(), s.end(), s.begin(), ::tolower);
					}
					class IXMLClass{
					public:
						virtual void getXMLParameters(std::string& xmlDoc, std::string& functionName, serpents::param::ParameterContainer& pc) = 0;
						template< typename T>
						T& generateXMLResponse(T& responseDoc, serpents::param::ParameterContainer& response){
							PugiXML* pugi = new PugiXML;
							pugi->generateXMLResponse(responseDoc, response);
							delete pugi;
							return responseDoc;
						}
						virtual std::string& generateXMLDoc(serpents::param::ParameterContainer& pc);
					};

					class PugiXML : public IXMLClass{
						void getXMLParameters(std::string& xmlDoc, std::string& functionName, serpents::param::ParameterContainer& pc){
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
						pugi::xml_document& generateXMLResponse(pugi::xml_document& responseDoc, serpents::param::ParameterContainer& response){
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
						std::string& generateXMLDoc(serpents::param::ParameterContainer& pc){
							pugi::xml_document responseDoc;
							generateXMLResponse(responseDoc, pc);
							std::stringstream ss;
							responseDoc.print(ss);
							return ss.str();
						}
					};

					class XMLFactory{
						static IXMLClass* iclass_;
					public:
						XMLFactory(){
							iclass_ = nullptr;
						}
						~XMLFactory(){
							delete iclass_;
						}
						static IXMLClass* getXMLParser(){
							iclass_ = new PugiXML;
							return iclass_;
						}
					};

				} //xml

			} //util
} //serpents

#endif // XMLUIL_H_