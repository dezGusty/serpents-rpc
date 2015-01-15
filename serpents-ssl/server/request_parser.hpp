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

#ifndef HTTP_SERVER4_REQUEST_PARSER_HPP
#define HTTP_SERVER4_REQUEST_PARSER_HPP

#include <string>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include "coroutine.hpp"
#include "serpents-ssl\base.h"
namespace serpents{
  namespace http {
    namespace server2 {

      struct request;

      /// Parser for incoming requests.
      class SSL_SERVER_API request_parser : coroutine
      {


      public:
        /// Parse some data. The tribool return value is true when a complete request
        /// has been parsed, false if the data is invalid, indeterminate when more
        /// data is required. The InputIterator return value indicates how much of the
        /// input has been consumed.
        template <typename InputIterator>
        boost::tuple<boost::tribool, InputIterator> parse(request& req,
          InputIterator begin, InputIterator end)
        {
          while (begin != end)
          {
            boost::tribool result = consume(req, *begin++);
            if (result || !result)
              return boost::make_tuple(result, begin);
          }
          boost::tribool result = boost::indeterminate;
          return boost::make_tuple(result, begin);
        }

      private:

        /// The name of the content length header.
        static std::string content_length_name_;

        /// Content length as decoded from headers. Defaults to 0.
        std::size_t content_length_ =0;

        /// Handle the next character of input.
        boost::tribool consume(request& req, char input);

        /// Check if a byte is an HTTP character.
        static bool is_char(int c);

        /// Check if a byte is an HTTP control character.
        static bool is_ctl(int c);

        /// Check if a byte is defined as an HTTP tspecial character.
        static bool is_tspecial(int c);

        /// Check if a byte is a digit.
        static bool is_digit(int c);

        /// Check if two characters are equal, without regard to case.
        static bool tolower_compare(char a, char b);

        /// Check whether the two request header names match.
        bool headers_equal(const std::string& a, const std::string& b);
      };


    } // namespace server4
  } // namespace http
} // namespace serpents

#endif // HTTP_SERVER4_REQUEST_PARSER_HPP