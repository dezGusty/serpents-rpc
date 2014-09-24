#include "gtest\gtest.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>
#include <cmath>
using namespace std;

TEST(fileLookUp, fileExists){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result2;
	myClient.call("http://localhost:8081/RPC2", "fileLookUp", "s", &result2, "D:\\test.txt");
	bool response = xmlrpc_c::value_boolean(result2);
	EXPECT_EQ(true, response);
}
TEST(fileLookUp, fileDoesNotExists){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result2;
	myClient.call("http://localhost:8081/RPC2", "fileLookUp", "s", &result2, "D:\\test.txt");
	bool response = xmlrpc_c::value_boolean(result2);
	EXPECT_EQ(true, response);
}
TEST(sleep, returns){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result2;
	myClient.call("http://localhost:8081/RPC2", "sleep", "i", &result2, 5);
	bool response = xmlrpc_c::value_boolean(result2);
	EXPECT_EQ(true, response);
}
TEST(getMean, positive){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::paramList getMeanParms;
	xmlrpc_c::value result;
	getMeanParms.add(xmlrpc_c::value_int(2));
	getMeanParms.add(xmlrpc_c::value_double(0.5));
	getMeanParms.add(xmlrpc_c::value_int(2));
	getMeanParms.add(xmlrpc_c::value_double(0.5));
	myClient.call("http://localhost:8081/RPC2", "getMean", getMeanParms, &result);
	float response = xmlrpc_c::value_double(result);
	float res = 2.0f;
	EXPECT_EQ(res, response);
}

TEST(getMean, negative){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::paramList getMeanParms;
	xmlrpc_c::value result;
	getMeanParms.add(xmlrpc_c::value_int(-2));
	getMeanParms.add(xmlrpc_c::value_double(-0.5));
	getMeanParms.add(xmlrpc_c::value_int(-2));
	getMeanParms.add(xmlrpc_c::value_double(-0.5));
	myClient.call("http://localhost:8081/RPC2", "getMean", getMeanParms, &result);
	float response = xmlrpc_c::value_double(result);
	float res = -2.0f;
	EXPECT_EQ(res, response);
}
TEST(getMean, other){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::paramList getMeanParms;
	xmlrpc_c::value result;
	getMeanParms.add(xmlrpc_c::value_int(4));
	getMeanParms.add(xmlrpc_c::value_double(0.5));
	getMeanParms.add(xmlrpc_c::value_int(4));
	getMeanParms.add(xmlrpc_c::value_double(0.5));
	myClient.call("http://localhost:8081/RPC2", "getMean", getMeanParms, &result);
	float response = xmlrpc_c::value_double(result);
	float res = 4.0f;
	EXPECT_EQ(res, response);
}
TEST(push){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result;
	myClient.call("http://localhost:8081/RPC2", "push", "s", &result, "test");
	bool pushResponse = xmlrpc_c::value_boolean(result);
	//EXPECT_EQ(true, result);
	
}
TEST(pop){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value result;
	myClient.call("http://localhost:8081/RPC2", "pop", "s", &result, "");

	std::string sr = xmlrpc_c::value_string(result);

	EXPECT_EQ("test",sr);
}
TEST(generateUUID){
	xmlrpc_c::clientSimple myClient;
	xmlrpc_c::value randomString;
	myClient.call("http://localhost:8081/RPC2", "generateUUID", "s", &randomString, "");
	std::string uuidResponse = xmlrpc_c::value_string(randomString);
	std::cout << uuidResponse << std::endl;
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}