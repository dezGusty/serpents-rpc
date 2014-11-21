#include <string>
#include <sstream>
#include <iostream>
#include "serpents-ssl\client\client.hpp"
#include "gtest\gtest.h"

namespace {
	class SSL_Server_Test : public ::testing::Test{
	protected:
		SSL_Server_Test() : resolver(io_service), query("localhost", "8080"), ctx(boost::asio::ssl::context::sslv23){
			
			iterator = resolver.resolve(query);
			ctx.load_verify_file("cacert.pem");
			c = new client(io_service, ctx, iterator);
		}
		virtual ~SSL_Server_Test(){
			delete c;
		}
		//server stuff
		client* c;
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::resolver resolver;
		boost::asio::ip::tcp::resolver::query query;
		boost::asio::ip::tcp::resolver::iterator iterator;
		boost::asio::ssl::context ctx;
	};
	TEST_F(SSL_Server_Test, add){
		serpents::ParameterContainer request;
		request.add(2);
		request.add(3);
		serpents::ParameterContainer reply;
		c->send("add", request, reply);
		EXPECT_EQ(5, reply.getInt(0));
	}

	TEST_F(SSL_Server_Test, generateUUID){
		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;
		c->send("generateUUID", request, reply);
		std::cout << reply.getString(0) << std::endl;
	}
	
	
	TEST_F(SSL_Server_Test, fileExists){
		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;
		std::string fileName("D:\\test.txt");
		request.add(fileName);
		c->send("fileLookUp", request, reply);
		EXPECT_EQ(true, reply.getBool(0));
	}
	TEST_F(SSL_Server_Test, fileDoesntExist){
		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;
		std::string fileName("D:\\test2.txt");
		request.add(fileName);
		c->send("fileLookUp", request, reply);
		EXPECT_EQ(false, reply.getBool(0));
	}
	
	TEST_F(SSL_Server_Test,push){
		serpents::ParameterContainer request = "test";
		serpents::ParameterContainer reply;
		c->send("push", request, reply);

		EXPECT_EQ(true, reply.getBool(0));

	}
	TEST_F(SSL_Server_Test,pop){
		serpents::ParameterContainer request;
		serpents::ParameterContainer reply;
		c->send("pop", request, reply);

		std::cout <<"reply:"<< reply.getString(0);
		EXPECT_EQ("test", reply.getString(0));
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