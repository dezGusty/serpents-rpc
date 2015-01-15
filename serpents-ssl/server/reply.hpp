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
//

#ifndef HTTP_SERVER2_REPLY_HPP
#define HTTP_SERVER2_REPLY_HPP

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include "header.hpp"
#include "serpents-ssl\base.h"
namespace serpents{
  namespace http {
    namespace server2 {

      /// A reply to be sent to a client.
      struct SSL_SERVER_API reply
      {
        class RequestHandler;
        friend RequestHandler;
        reply(const reply& repl);
        reply();
        ~reply();
        /// The status of the reply.
        enum status_type
        {
          ok = 200,
          created = 201,
          accepted = 202,
          no_content = 204,
          multiple_choices = 300,
          moved_permanently = 301,
          moved_temporarily = 302,
          not_modified = 304,
          bad_request = 400,
          unauthorized = 401,
          forbidden = 403,
          not_found = 404,
          internal_server_error = 500,
          not_implemented = 501,
          bad_gateway = 502,
          service_unavailable = 503
        } status = status_type::created;
        
        /// Convert the reply into a vector of buffers. The buffers do not own the
        /// underlying memory blocks, therefore the reply object must remain valid and
        /// not be changed until the write operation has completed.
        std::vector<boost::asio::const_buffer> to_buffers();

        /// set/get for content reply
        void setContent(std::string& content);
        std::string& getContent() const;

        ///get headers
        std::vector<header>& getHeaders() const;

        /// Get a stock reply.
        static void stock_reply(status_type status, std::string content, reply& reply);
        static void reply::stock_reply(reply::status_type status, reply& reply);
      private:
        class Impl;
        Impl* Impl_;
      };
      

    } // namespace server2
  } // namespace http
}// serpents

#endif // HTTP_SERVER2_REPLY_HPP