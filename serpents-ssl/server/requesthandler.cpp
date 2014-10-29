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

#include <thread>
#include <chrono>
#include <iostream>

// project libs 

namespace serpents{
	namespace http{
		namespace server2{
			void RequestHandler::handleRequest(request& req, reply& rep, ServerFunctionRepository& functionRepo){

				rep.status = reply::status_type::ok;

				serpents::param::ParameterContainer pc;
				std::string funcname;
				util::xml::IXMLClass* xmlutil = new util::xml::PugiXML;
				xmlutil->getXMLParameters(req.content, funcname, pc);
				sptr_method method = functionRepo.lookUpMethod(funcname);

				serpents::param::ParameterContainer result;
				method->execute(&pc, &result);

				pugi::xml_document responseDoc;
				xmlutil->generateXMLResponse(responseDoc, result);
				std::stringstream ss;
				responseDoc.print(ss);

				ss << "\n\0";
				rep.setContent(ss.str());
				rep.getHeaders().resize(2);
				rep.getHeaders()[0].name = "Content-Length";
				rep.getHeaders()[0].value = (boost::lexical_cast<std::string>(rep.getContent().length()));
				rep.getHeaders()[1].name = ("Content-Type");
				rep.getHeaders()[1].value = ("application/xml");

			}



		}
	}
} // namespace serpents