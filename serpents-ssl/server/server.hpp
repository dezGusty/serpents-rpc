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

// based of the ASIO Server guide found at http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html

#ifndef SSL_SERVER_H_
#define SSL_SERVER_H

#include "serpents-ssl\base.h"
#include "serpents-ssl\util\xmlutil.hpp"
#include "serpents-ssl\server\session.hpp"
namespace serpents{
	namespace ssl{
		class SSL_SERVER_API server
		{
			class Impl;
			Impl* Impl_;
		public:
			server(const std::string& address, boost::asio::io_service& io_service, unsigned short port, size_t& numOfThreads);
			~server();
			http::server2::ServerFunctionRepository& getfunctionRepo();
			void run();
			void stop();
			void startSession();
			std::string server::get_password() const;
			void handle_accept(session* new_session,const boost::system::error_code& error);
		};

	}
} // namespace serpents
#endif /// SSL_SERVER_H_