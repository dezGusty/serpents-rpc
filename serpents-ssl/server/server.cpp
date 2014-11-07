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


///serve no purpose yet but C++ wouldn't create the .lib file without the cpp file.

#include "server.hpp"
namespace serpents{
	namespace ssl{
		class server::Impl{
			friend server;
			boost::asio::io_service& io_service_;
			boost::asio::ip::tcp::acceptor acceptor_;
			boost::asio::ssl::context context_;

			/// The incoming request.
			http::server2::request request_;

			/// The parser for the incoming request.
			http::server2::request_parser request_parser_;

			/// The reply to be sent back to the client.
			http::server2::reply reply_;

			/// The number of threads that will call io_service::run().
			std::size_t thread_pool_size_;
			///function repository 
			http::server2::ServerFunctionRepository functionRepo;
			std::vector<std::shared_ptr<std::thread> > threads;

			Impl(const std::string& address, boost::asio::io_service& io_service, unsigned short port, size_t& numOfThreads)
				: io_service_(io_service),
				acceptor_(io_service,
				boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
				context_(io_service, boost::asio::ssl::context::sslv23),
				thread_pool_size_(numOfThreads)
			{
				//
			}
		};
		server::server(const std::string& address, boost::asio::io_service& io_service, unsigned short port, size_t& numOfThreads)
			//	: io_service_(io_service),
			//	acceptor_(io_service,
			//	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
			//	context_(io_service, boost::asio::ssl::context::sslv23),
			//	thread_pool_size_(numOfThreads)
		{
			try{
				Impl_ = new Impl(address, io_service, port, numOfThreads);

				Impl_->context_.set_options(
					boost::asio::ssl::context::default_workarounds
					| boost::asio::ssl::context::no_sslv2
					| boost::asio::ssl::context::single_dh_use);
				Impl_->context_.set_password_callback(boost::bind(&server::get_password, this));
				Impl_->context_.use_certificate_chain_file("cacert.pem");
				Impl_->context_.use_private_key_file("private.pem", boost::asio::ssl::context::pem);
				Impl_->context_.use_tmp_dh_file("dh512.pem");

				session* new_session = new session(Impl_->io_service_, Impl_->context_, Impl_->functionRepo);
				Impl_->acceptor_.async_accept(new_session->socket(),
					boost::bind(&server::handle_accept, this, new_session,
					boost::asio::placeholders::error));
			}
			catch (std::exception e){
				std::cout << e.what() << std::endl;
			}
			//run();
		}
		server::~server(){
			delete Impl_;
		}
		void server::stop(){
			Impl_->io_service_.stop();
		}

		http::server2::ServerFunctionRepository& server::getfunctionRepo(){
			return Impl_->functionRepo;
		}

		void server::run(){

			for (std::size_t i = 0; i < Impl_->thread_pool_size_; ++i)
			{
				std::shared_ptr<std::thread> thread(new std::thread(
					boost::bind(&server::startSession, this)));
				Impl_->threads.push_back(thread);
			}

			// Wait for all threads in the pool to exit.
			for (std::size_t i = 0; i < Impl_->threads.size(); ++i)
				Impl_->threads[i]->join();
		}
		void server::startSession(){
			Impl_->io_service_.run();
			session* new_session = new session(Impl_->io_service_, Impl_->context_, Impl_->functionRepo);
			Impl_->acceptor_.async_accept(new_session->socket(),
				boost::bind(&server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
			delete new_session;
		}

		std::string server::get_password() const
		{
			return "test";
		}

		void server::handle_accept(session* new_session,
			const boost::system::error_code& error)
		{
			if (!error)
			{
				new_session->start();
				new_session = new session(Impl_->io_service_, Impl_->context_, Impl_->functionRepo);
				Impl_->acceptor_.async_accept(new_session->socket(),
					boost::bind(&server::handle_accept, this, new_session,
					boost::asio::placeholders::error));
			}
			else
			{
				delete new_session;
			}
		}


	}
}