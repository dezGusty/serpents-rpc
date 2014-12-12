#include <string>
#include <sstream>
#include "serpents-ssl\client\client.hpp"
#include "gtest\gtest.h"
#include <memory>
#include <vector>
#include <thread>
namespace {
  class SSL_Server_Test : public ::testing::Test{
  protected:
    SSL_Server_Test() : resolver(io_service), query("localhost", "8081"), ctx(boost::asio::ssl::context::sslv23){
      
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

  class SSL_Server_Other {
  public:
    SSL_Server_Other() : resolver(io_service), query("localhost", "8081"), ctx(boost::asio::ssl::context::sslv23){

      iterator = resolver.resolve(query);
      ctx.load_verify_file("cacert.pem");
      c = new client(io_service, ctx, iterator);
    }
    virtual ~SSL_Server_Other(){
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
    c->send("add", &request, &reply);
    EXPECT_EQ(5, reply.getInt(0));
  }

  TEST_F(SSL_Server_Test, generateUUID){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    c->send("generateUUID", &request, &reply);
    std::cout << reply.getString(0) << std::endl;
  }
  
  
  TEST_F(SSL_Server_Test, fileExists){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    std::string fileName("D:\\test.txt");
    request.add(fileName);
    c->send("fileLookUp", &request, &reply);
    EXPECT_EQ(true, reply.getBool(0));
  }
  TEST_F(SSL_Server_Test, fileDoesntExist){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    std::string fileName("D:\\test2.txt");
    request.add(fileName);
    c->send("fileLookUp", &request, &reply);
    EXPECT_EQ(false, reply.getBool(0));
  }

  
  TEST_F(SSL_Server_Test,push){
    serpents::ParameterContainer request;
    request.add("test");
    serpents::ParameterContainer reply;
    c->send("push", &request, &reply);

    EXPECT_EQ(true, reply.getBool(0));

  }
  TEST_F(SSL_Server_Test,pop){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    c->send("pop", &request, &reply);

    std::cout <<"reply:"<< reply.getString(0)<<std::endl;
    EXPECT_EQ("test", reply.getString(0));
  }
  TEST_F(SSL_Server_Test, getMean){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    request.add(2, 0.5, 2,0.5);

    c->send("getMean", &request, &reply);
    double res = 2.0;
    EXPECT_EQ(res, reply.getDouble(0));
  }
  TEST_F(SSL_Server_Test, getMeanNegative){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    request.add(-2, -0.5, -2, -0.5);

    c->send("getMean", &request, &reply);
    double res = -2.0;
    EXPECT_EQ(res, reply.getDouble(0));
  }

  TEST_F(SSL_Server_Test, sleep){
    serpents::ParameterContainer request;
    request.add(1);
    serpents::ParameterContainer reply;
    c->send("sleep", &request, &reply);
    EXPECT_EQ(true, reply.getBool(0));
  }
  TEST_F(SSL_Server_Test, getMeanOther){
    serpents::ParameterContainer request;
    serpents::ParameterContainer reply;
    request.add(4, 0.5, 4, 0.5);

    c->send("getMean", &request, &reply);
    double res = 4;
    EXPECT_EQ(res, reply.getDouble(0));
  }
  

   
}

int main(int argc, char* argv[])
{
 
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}