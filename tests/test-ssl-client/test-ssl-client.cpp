#include <string>
#include <sstream>
#include <iostream>
#include "client\client.hpp"


int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query("localhost", "8080");
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
		ctx.load_verify_file("cacert.pem");

		client c(io_service, ctx, iterator);

		serpents::param::ParameterContainer request;
		serpents::param::ParameterContainer reply;
		std::string s = "hello";

		request.add(9,10);
		c.send("echo", request, reply);
		std::cout << reply.size();
		for each (auto  var in reply.getAll())
		{
			std::cout << var << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}