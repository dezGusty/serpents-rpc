//
// header.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


// based of the ASIO Server guide found at http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/examples/cpp11_examples.html
#ifndef HTTP_SERVER2_HEADER_HPP
#define HTTP_SERVER2_HEADER_HPP

#include <string>
#include "serpents-ssl\base.h"
namespace serpents{
	namespace http {
		namespace server2 {

			class header
			{
			public:
				std::string name;
				std::string value;
			};


		} // namespace server2
	} // namespace http
} // serpents
#endif // HTTP_SERVER2_HEADER_HPP