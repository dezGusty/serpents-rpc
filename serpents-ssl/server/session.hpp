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

#ifndef SESSION_H_
#define SESSION_H_
#pragma once
/// boost libs
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>
/// programs libs
#include "serpents-ssl\server\serverfunctionrepository.h"
#include "serpents-ssl\server\requesthandler.h"
#include "serpents-ssl\server\request_parser.hpp"
#include "serpents-ssl\server\reply.hpp"
#include "serpents-ssl\base.h"

///system libs

namespace serpents{
  namespace ssl{
    
    enum SSL_SERVER_API ErrorCodes {
      SUCCESS = 0,
      BAD_ARGUMENTS,
      ACCEPTOR_FAILURE,
      CONNECTION_FAILURE,
      WRITE_FAILURE,
      READ_FAILURE,
      SOCKET_CLOSE_FAILURE,
      UNSUPPORTED_REQUEST
    };

    typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

    class SSL_SERVER_API session
    {
      class Impl;
      Impl* Impl_;
    public:
      session(const session&) = delete;
      session(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
        http::server2::ServerFunctionRepository& repo);
      ~session();
      ssl_socket::lowest_layer_type& socket();
      void start();
      void handle_handshake(const boost::system::error_code& error);
      void handle_read(const boost::system::error_code& error,
        size_t bytes_transferred);
      void handle_write(const boost::system::error_code& error);
    };

    

  } //ssl
} //serpents

#endif //SESSION_H_