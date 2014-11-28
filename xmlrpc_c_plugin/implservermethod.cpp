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
//  project libs

#include "..\xmlrpc_c_plugin\implservermethod.h"
#include "retvalue.h"
#include "serpents\rpc\parameters\parametercontainer.hpp"
#include "serpents\rpc\log\log.h"

// system libs 
#include <iostream>
#include <string>

namespace serpents
{
  std::mutex mtx;

  void XmlRPC_CMethod::execute(xmlrpc_c::paramList const& paramList,  //  execute
                                    xmlrpc_c::value *   const  retvalP)
  {  
  serpents::ParameterContainer pc;
  try
  {
    fillParameterContainer(pc, paramList);
    XMLRPC_CRetValue rv;
    method->execute(&pc, &rv);  //  execute
    *retvalP = *(rv.getValue());
  }
  catch (const std::exception& e)
  {
#ifdef USE_LOG4CPP  //  logging starts
    Log::getPtr()->info(std::string("In method ") + method->getName());
    Log::getPtr()->error(e.what());
#endif  //  logging ends;
   }

#ifdef USE_LOG4CPP  //  logging starts
  Log::getPtr()->info(std::string("In method ") + method->getName());
  std::stringstream ss;
  ss << "  Input parameter: ";
  for each (auto var in pc.getAll())
  {
    ss << var << " ";
  }
  Log::getPtr()->info(ss.str());
  ss.str(std::string());
  ss.clear();
  int type = (*retvalP).type();
  switch (type)
  {
    //  int
    case xmlrpc_c::value::TYPE_INT:
      ss << "  Result: " << (static_cast<int>(static_cast<xmlrpc_c::value_int>(*(retvalP))));
    break;

    //  bool
    case xmlrpc_c::value::TYPE_BOOLEAN:
      ss << "  Result: " << (static_cast<bool>(static_cast<xmlrpc_c::value_boolean>(*(retvalP))));
    break;

    //  double
    case xmlrpc_c::value::TYPE_DOUBLE:
      ss << "  Result: " << (static_cast<double>(static_cast<xmlrpc_c::value_double>(*(retvalP))));
    break;

    //  string
    case xmlrpc_c::value::TYPE_STRING:
      ss << "  Result: " << (static_cast<std::string>(static_cast<xmlrpc_c::value_string>(*(retvalP))));
    break;
  }
  Log::getPtr()->info(ss.str());
    
#endif  //  logging ends; 
  }
  void XmlRPC_CMethod::fillParameterContainer(serpents::ParameterContainer& pc, const xmlrpc_c::paramList& paramList)
  {
    int parameterListSize(paramList.size());
    for (int i = 0; i < parameterListSize; i++)
    {
      xmlrpc_c::value value = paramList[i];
      int type = value.type();
      switch (type)
      {
        //  int
        case xmlrpc_c::value::TYPE_INT: 
          pc.add(paramList.getInt(i)); 
        break;
          //  bool
        case xmlrpc_c::value::TYPE_BOOLEAN: 
          pc.add(paramList.getBoolean(i));
        break;
          //  double
        case xmlrpc_c::value::TYPE_DOUBLE: 
          pc.add(paramList.getDouble(i));
        break;
          //  string
        case xmlrpc_c::value::TYPE_STRING: 
          pc.add(paramList.getString(i));
        break;
      }
    }
  }
  XmlRPC_CMethod::XmlRPC_CMethod() :xmlrpc_c::method()
  {
    method = nullptr;
  }
  void XmlRPC_CMethod::setSignatureAndHelp()
  {
    this->_signature = method->getSignature();
  }
  XmlRPC_CMethod::XmlRPC_CMethod(Method* method)
  {
    XmlRPC_CMethod();
    this->method = method;
    this->setSignatureAndHelp();
  }
}