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

#ifndef XMLUIL_H_
#define XMLUIL_H_
#pragma once 
//boost libs 
#include "boost\lexical_cast.hpp"

// system libs 
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
//pugixml 
//  #define PUGIXML_HEADER_ONLY
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
            virtual std::string generateErrorResponseDoc(std::string& content, int faultCode)=0;
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
            void handleErrorCases(pugi::xml_document& doc){
            
            }
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
              //  throw(std::exception("No supported variable types found"));
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
              //  pugi::xml_node var = param.child("value");
              //  for (var; var; var = param.next_sibling("value"))
              //  {
              //    std::string nodeWithCorectStructure = var.first_child().child_value();
              //  }
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
              
              if (!foundParams){
                pugi::xml_node strct = root.child("fault").child("value").child("struct");
                if (!strct == NULL){
                  std::string s = strct.last_child().child("value").child_value();
                  if (!s.compare("") == 0){
                    delete doc;
                    throw(std::exception(s.c_str()));
                  }
                }
                else{
                  delete doc;
                  throw(std::exception("No supported variable types found"));
                }
                
              }
              delete doc;
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
              xmlDoc.save(ss, "  ", pugi::format_raw); // easier for client to read in raw format 
                                   // \n and    screws with the parser 
                                  

              
              return ss.str();
            }
            std::string generateErrorResponseDoc(std::string& content, int faultCode){
              pugi::xml_document xmlDoc;

              //place nodes in xml doc
              pugi::xml_node root = xmlDoc.append_child("methodResponse");
              pugi::xml_node fault = root.append_child("fault");
              pugi::xml_node value =fault.append_child("value");
              pugi::xml_node strct = value.append_child("struct");
              pugi::xml_node falutCodeMember = strct.append_child("member");
              pugi::xml_node falutCodeMemberName = falutCodeMember.append_child("name");
              falutCodeMemberName.append_child(pugi::node_pcdata).set_value("faultCode");
              falutCodeMember.append_child("value").append_child("int")
                      .append_child(pugi::node_pcdata).set_value(std::to_string(faultCode).c_str());
              pugi::xml_node falutStringMember = strct.append_child("member");
              pugi::xml_node falutStringMemberName = falutStringMember.append_child("name");
              falutStringMemberName.append_child(pugi::node_pcdata).set_value("faultString");
              pugi::xml_node falutStringMemberValue =falutStringMember.append_child("value");
              falutStringMemberValue.append_child(pugi::node_pcdata).set_value(content.c_str());
              // get string from xml_document
              std::stringstream ss;
              xmlDoc.save(ss, "  ", pugi::format_raw); // easier for client to read in raw format 
              return ss.str();
            }
          };
          // instance must be deleted by user
          class XMLParserFactory{
            static IXMLClass* instance;
            public:
              static IXMLClass* getParser(std::string parserName)  {
                if (parserName.compare("pugixml")==0){
                  if (instance == nullptr){
                    instance = new PugiXML;
                  }
                }
                return instance;
              }

              XMLParserFactory() = delete;
              XMLParserFactory(const XMLParserFactory& c) = delete;
          };

        } //xml

      } //util
} //serpents

#endif // XMLUIL_H_/