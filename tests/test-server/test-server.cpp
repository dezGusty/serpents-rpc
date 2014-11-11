//serpents libs
#include "serpents\rpc\server\repository.h"
#include "serpents\rpc\server\server.h"
#include "serpents\rpc\server\rpcselector.h"


//c++ system libs
#include <fstream>
#include <random>
#include <thread>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

serpents::ParameterContainer* internalContainer;

class GenerateRandomString: public  serpents::Method {
	public:
	GenerateRandomString(){
		setSignature(std::string("s:b"));
		setHelp(std::string("random characters(uuri format)"));
		setName("generateUUID");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		
		std::string result; 
		fillWithRandomChars(&result, 8);
		fillWithRandomChars(&result, 4);
		fillWithRandomChars(&result, 4);
		fillWithRandomChars(&result, 4);
		fillWithRandomChars(&result, 12);
		rv->setValue(result);
	}

	void fillWithRandomChars(std::string* s, int n){
		if (!s->empty()){
			s->push_back('-');
		}
		std::random_device generator;
		std::uniform_int_distribution<uint32_t> distribution(97, 122); 
		
		for (int i = 0; i < n; i++){
			int charIndex = distribution(generator);
			s->push_back(static_cast<char>(charIndex));
		}
	}
	

};
void main(){
	internalContainer = new serpents::ParameterContainer();
	serpents::Server server;
	server.addLogTarget("default", "D:\\program.log");

	GenerateRandomString* rpc = new GenerateRandomString();
	
	serpents::FunctionRepository fr;
	
	fr.addMethod(rpc);
	
	server.setRepository(fr);
	serpents::RPCSelector rpcselect;
	rpcselect.selectRPCMethod(server, "xmlrpc_plugin");
//	server.getXMLRPC_CServerOptions()->portNumber(8081);
//	server.getXMLRPC_CServerOptions()->uriPath("/RPC2");
//	server.getXMLRPCPP_ServerOptions()->setPort(8081);
	rpcselect.startServer();
	
	
}