#include <string>
#include <sstream>
#include <iostream>
#include "serpents-ssl\client\client.hpp"
#include "gtest\gtest.h"

namespace {
	class SSL_Server_Test : public ::testing::Test{
	protected:
		SSL_Server_Test() {
			boost::asio::io_service io_service;
			boost::asio::ip::tcp::resolver resolver(io_service);
			boost::asio::ip::tcp::resolver::query query("localhost", "8080");
			boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

			boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
			ctx.load_verify_file("cacert.pem");

			c = new client(io_service, ctx, iterator);
		}
		virtual ~SSL_Server_Test(){
			delete c;
		}

		//server stuff
		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;
		client* c;
	};

	TEST_F(SSL_Server_Test, fileExists){
		std::string fileName("D:\\test.txt");
		c->send("fileLookUp", request, reply);
		EXPECT_EQ(true, reply.getInt(1));
	}
	TEST_F(SSL_Server_Test, fileDoesntExist){
		std::string fileName("D:\\test2.txt");
		c->send("fileLookUp", request, reply);
		EXPECT_EQ(false, reply.getInt(0));
	}
	TEST_F(SSL_Server_Test, sleep){
		c->send("sleep", request, reply);
		EXPECT_EQ(true, reply.getInt(0));
	}
	TEST_F(SSL_Server_Test, getMeanpositive){

	}
	TEST_F(SSL_Server_Test, getMeannegative){

	}
	TEST_F(SSL_Server_Test, getMeanother){

	}
	TEST_F(SSL_Server_Test, push){

	}
	TEST_F(SSL_Server_Test, pop){

	}
	TEST_F(SSL_Server_Test, generateUUID){
		c->send("generateUUID", request, reply);
		std::cout << reply.getString(0) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	/*
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query("localhost", "8080");
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
		ctx.load_verify_file("cacert.pem");

		client c(io_service, ctx, iterator);

		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;

		request.add(9,10);
		c.send("generateUUID", request, reply);
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
	*/
}