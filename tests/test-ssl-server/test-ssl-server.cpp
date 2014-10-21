#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include "server/server.hpp"

using namespace serpents::ssl;

int main(){

	try{
		boost::asio::io_service io_service;
		size_t numThreads = 3;

		server s("localhost", io_service, 8080, numThreads);

		std::shared_ptr<serpents::http::server2::ServerMethod> s_method(new serpents::http::server2::SampleMethod);
		s_method->setName(std::string("sample"));
		s.getfunctionRepo().addServerMethod(s_method);
		std::shared_ptr<serpents::http::server2::ServerMethod> s2_method(new serpents::http::server2::EchoMethod);
		s2_method->setName(std::string("echo"));
		s.getfunctionRepo().addServerMethod(s2_method);

		std::shared_ptr<serpents::http::server2::ServerMethod> s3_method(new serpents::http::server2::WriteToFile);
		s3_method->setName(std::string("write"));
		s.getfunctionRepo().addServerMethod(s3_method);
		s.run();
	}
	catch (std::exception& e){
		std::cerr << e.what()<<std::endl;
	}
}