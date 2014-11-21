#include "serpents-ssl\server\server.hpp"
namespace serpents{
	namespace ssl{
		class session::Impl{
			friend session;
			Impl(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
				http::server2::ServerFunctionRepository& repo);

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
		session::Impl::Impl(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
			http::server2::ServerFunctionRepository& repo)
			: socket_(io_service, context),
			functionRepo_(repo)
		{
		
		}
		session::session(boost::asio::io_service& io_service, boost::asio::ssl::context& context,
			http::server2::ServerFunctionRepository& repo)

		{
			Impl_ = new Impl(io_service, context, repo);
		}
		session::~session(){
			delete Impl_;
		}
		ssl_socket::lowest_layer_type& session::socket()
		{
			return Impl_->socket_.lowest_layer();
		}

		void session::start()
		{
			Impl_->socket_.async_handshake(boost::asio::ssl::stream_base::server,
				boost::bind(&session::handle_handshake, this,
				boost::asio::placeholders::error));
		}

		void session::handle_handshake(const boost::system::error_code& error)
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

		void session::handle_read(const boost::system::error_code& error,
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
					catch (serpents::ParamContainerException& e){
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

		void session::handle_write(const boost::system::error_code& error)
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
	}
}