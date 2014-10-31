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

/// boost libs
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>
/// programs libs
#include "server\serverfunctionrepository.h"
#include "server\requesthandler.h"
#include "server\request_parser.hpp"
#include "server\reply.hpp"
#include "base.h"
#include "log\log.h"
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
			class Impl{
				friend session;
				Impl(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
					http::server2::ServerFunctionRepository& repo)
					: socket_(io_service, context),
					functionRepo_(repo)
				{
				}
				
				ssl_socket socket_;
				boost::array<char, 8192> buffer_;
				///function repository 
				http::server2::ServerFunctionRepository& functionRepo_;

				/// The incoming request.
				http::server2::request request_;

				/// The parser for the incoming request.
				http::server2::request_parser request_parser_;

				/// The reply to be sent back to the client.
				http::server2::reply reply_;
				
			};
			Impl* Impl_;
		public:
			session(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
				http::server2::ServerFunctionRepository& repo)

			{
				Impl_ = new Impl(io_service, context, repo);
			}
			~session(){
				delete Impl_;
			}
			ssl_socket::lowest_layer_type& socket()
			{
				return Impl_->socket_.lowest_layer();
			}

			void start()
			{
				Impl_->socket_.async_handshake(boost::asio::ssl::stream_base::server,
					boost::bind(&session::handle_handshake, this,
					boost::asio::placeholders::error));
			}

			void handle_handshake(const boost::system::error_code& error)
			{
				if (!error)
				{
					Impl_->socket_.async_read_some(boost::asio::buffer(Impl_->buffer_),
						boost::bind(&session::handle_read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
				}
				else
				{
					delete this;
				}
			}

			void handle_read(const boost::system::error_code& error,
				size_t bytes_transferred)
			{
				if (!error)
				{

					std::stringstream ss(Impl_->buffer_.data());
					//parseRequest(ss);
					std::string cont = ss.str();
					http::server2::request_parser rp;
					boost::tribool result;
					boost::tie(result, boost::tuples::ignore) = rp.parse(Impl_->request_, cont.begin(), cont.end());

					if (result){
						http::server2::RequestHandler* requestHandler = new http::server2::RequestHandler;
						try{
							requestHandler->handleRequest(Impl_->request_, Impl_->reply_, Impl_->functionRepo_);

							//	boost::asio::async_write(socket_, rep.to_buffers(),
							//boost::bind(&session::handle_write, this,
							//	boost::asio::placeholders::error));
						}
						catch (boost::bad_lexical_cast& e){
							LOG_ERROR(e.what());
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, e.what());
						}
						catch (serpents::param::ParamContainerException& e){
							LOG_ERROR(e.what());
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, e.what());
						}
						catch (http::server2::RepoException& e){
							LOG_ERROR(e.what());
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, e.what());

						}
						catch (http::server2::RequestException& e){
							LOG_ERROR(e.what());
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, "unknown exception");
						}
						catch (std::exception& e){
							LOG_ERROR(e.what());
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, e.what());

						}
						catch (...){
							LOG_ERROR("unkown exception");
							Impl_->reply_ = http::server2::reply::stock_reply(http::server2::reply::ok, "unkonwn exception");

						}

						boost::asio::async_write(Impl_->socket_, Impl_->reply_.to_buffers(),
							boost::bind(&session::handle_write, this,
							boost::asio::placeholders::error));
						delete requestHandler;

					}

				}
				else
				{
					delete this;
				}
			}
			/*
			// If an error occurs then no new asynchronous operations are started. This
			// means that all shared_ptr references to the connection object will
			// disappear and the object will be destroyed automatically after this
			// handler returns. The connection class's destructor closes the socket.
			}
			*/

			void handle_write(const boost::system::error_code& error)
			{
				if (!error)
				{
					Impl_->socket_.async_read_some(boost::asio::buffer(Impl_->buffer_),
						boost::bind(&session::handle_read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
				}
				else
				{
					delete this;
				}
			}
		};



	} //ssl
} //serpents