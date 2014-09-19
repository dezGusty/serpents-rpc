#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cstdlib>
#include <string>
#include <iostream>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>
#include <cmath>
using namespace std;

/*
int main(int argc ){
if (argc-1 > 0) {
cerr << "This program has no arguments" << endl;
exit(1);
}

try {
string const serverUrl("http://localhost:8080/RPC2");

xmlrpc_c::clientSimple myClient;



xmlrpc_c::value result2;

myClient.call(\"http://localhost:8081/RPC2\", "fileLookUp", "s", &result2, "D:\\test.txt");


bool b = xmlrpc_c::value_boolean(result2);
// Assume the method returned a boolean; throws error if not

cout << "FileFound: " << b << endl;
xmlrpc_c::value result;
myClient.call(\"http://localhost:8081/RPC2\", "sum","ii", &result, 5, 7);
int const sum = xmlrpc_c::value_int(result);
cout << "Result of RPC (sum of 5 and 7): " << sum << endl;


} catch (exception const& e) {
cerr << "Client threw error: " << e.what() << endl;
} catch (...) {
cerr << "Client threw unexpected error." << endl;
}

return 0;
}

*/

SCENARIO("XMLRPC Testing"){
	xmlrpc_c::clientSimple myClient;
	
	GIVEN("bool doesFileExist(string fileName)"){
		try {
			xmlrpc_c::value result2;
			WHEN("The file queried exists"){
				THEN("The method returns true"){
					myClient.call("http://localhost:8081/RPC2", "fileLookUp", "s", &result2, "D:\\test.txt");
					bool response = xmlrpc_c::value_boolean(result2);
					REQUIRE(response == true);
				}
			}
			WHEN("The file queried does not exist"){
				THEN("The method returns false"){
					myClient.call("http://localhost:8081/RPC2", "fileLookUp", "s", &result2, "D:\\test2.txt");
					bool response = xmlrpc_c::value_boolean(result2);
					REQUIRE(response == false);
				}
			}
		}
		catch (exception const& e) {
			cerr << "Client threw error: " << e.what() << endl;
		}
		catch (...) {
			cerr << "Client threw unexpected error." << endl;
		}
	}
	
	GIVEN("float getMean(int value1, float weight1, int value2, float weight2)"){
		try {
			xmlrpc_c::value result;
			WHEN("parameters are 1, 0.5, 1,0.5"){
				THEN("Response is 42"){
					xmlrpc_c::clientSimple myClient;
					xmlrpc_c::paramList getMeanParms;
					getMeanParms.add(xmlrpc_c::value_int(2));
					getMeanParms.add(xmlrpc_c::value_double(0.5));
					getMeanParms.add(xmlrpc_c::value_int(2));
					getMeanParms.add(xmlrpc_c::value_double(0.5));
					myClient.call("http://localhost:8081/RPC2", "getMean", getMeanParms, &result);
				
					float response = xmlrpc_c::value_double(result);

					float result = 2.0f;
					REQUIRE(response == result);
				}
			}
		}
		catch (exception const& e) {
			cerr << "Client threw error: " << e.what() << endl;
		}
		catch (...) {
			cerr << "Client threw unexpected error." << endl;
		}
	}
	
		GIVEN("push/pop"){
			try {

				WHEN("PUSH value \"test\""){
					THEN("expect true"){
						xmlrpc_c::value result;
						
						myClient.call("http://localhost:8081/RPC2", "push", "s", &result, "test");
						bool pushResponse = xmlrpc_c::value_boolean(result);
						bool res = true;
						REQUIRE(res == pushResponse);
					}
				}
				WHEN("Pop value"){
					THEN("Expect test"){
						xmlrpc_c::value result;
						myClient.call("http://localhost:8081/RPC2", "pop", "s", &result, "");
						
						std::string sr = xmlrpc_c::value_string(result);
						REQUIRE(strcmp(sr.c_str(), "test") == 0);
					}
				}
			}
			catch (exception const& e) {
				cerr << "Client threw error: " << e.what() << endl;
			}
			catch (...) {
				cerr << "Client threw unexpected error." << endl;
			}
		}
		GIVEN("generate uuid"){
			WHEN("string getRandomToken()"){
				THEN("Random string"){
					xmlrpc_c::value randomString;
					myClient.call("http://localhost:8081/RPC2", "generateUUID", "s", &randomString, "");
					std::string uuidResponse = xmlrpc_c::value_string(randomString);
					std::cout << uuidResponse << std::endl;
				}
			}
		}
		
	}


