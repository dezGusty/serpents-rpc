//serpents libs
#include "serpents/rpc/server/repository.h"
#include "serpents/rpc/server/server.h"
#include "serpents/rpc/server/RPCSelector.h"

//c++ system libs
#include <fstream>
#include <random>
#include <thread>
#include <iostream>
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

class RPCMethod :public  serpents::Method{
	public:
	RPCMethod(){
		setSignature(std::string("s:b"));
		setHelp(std::string("this method looks up if a file exists at a given path"));
		setName("fileLookUp");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		std::string filePath(parameters->getString(0));
		std::ifstream file(filePath);
		if (file.good()){
			rv->setValue(true);
		}
		else{
			rv->setValue(false);
		}
	
		file.close();
	}
	
	
	
};

class RPCMethod2 :public  serpents::Method{
public:
	RPCMethod2(){
	
		setSignature(std::string("i:ii"));
		setHelp(std::string("this method adds two ints together"));
		setName("add");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		int sum= 0;
		sum = parameters->getInt(0) + parameters->getInt(1);
		rv->setValue(sum);
	}
	
};

class GetMean : public serpents::Method{
public:
	GetMean(){
		
		setSignature(std::string("i:ii"));
		setHelp(std::string("returns mean average"));
		setName("getMean");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		
		double sum1 = 0;
		double sum2 = 0;
		for (unsigned int i = 0; i < parameters->size() - 1; i += 2){
			int intNum = parameters->getInt(i);
			double doubleNum = parameters->getDouble(i + 1);
			sum1 += intNum*doubleNum;
			sum2 += doubleNum;
		}
		
		rv->setValue((double)sum1 / sum2);
	}
	
};

class PushInternalValue : public serpents::Method{
public:
	PushInternalValue(){
		
		setSignature(std::string("s:s"));
		setHelp(std::string("returns mean average"));
		setName("push");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		internalContainer->push(parameters->getString(0));
		rv->setValue(true);
	}
	
};
class PopInternalValue : public serpents::Method{
public:
	PopInternalValue(){
		setSignature(std::string("s:s"));
		setHelp(std::string("returns mean average"));
		setName("pop");

	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		rv->setValue(internalContainer->pop());
		
	}
	

};


class JustSleep: public serpents::Method{
public:
	JustSleep(){
		setSignature(std::string("i:"));
		setHelp(std::string("sleeps for i ammount of ttime * 1000"));
		setName("sleep");
	}
	
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		int i = parameters->getInt(0);
		std::chrono::milliseconds dura(i * 1000);
		std::this_thread::sleep_for(dura);
		rv->setValue(true);
	}
};

void main(){
	internalContainer = new serpents::ParameterContainer();
	serpents::Server server;
	server.addLogTarget("default", "D:\\program.log");

	RPCMethod* rpc = new RPCMethod();
	RPCMethod2* rpc2 = new RPCMethod2();
	GetMean* getmean = new GetMean();
	PushInternalValue* push = new PushInternalValue();
	PopInternalValue* pop = new PopInternalValue();
	GenerateRandomString* gen = new GenerateRandomString();
	JustSleep* js = new JustSleep();
	serpents::FunctionRepository fr;
	
	fr.addMethod(rpc);
	fr.addMethod(rpc2);
	fr.addMethod(getmean);
	fr.addMethod(pop);
	fr.addMethod(push);
	fr.addMethod(gen);
	fr.addMethod(js);
	
	server.setRepository(fr);
	serpents::RPCSelector rpcselect;
	rpcselect.selectRPCMethod(server, "xmlrpc_c");
//	server.getXMLRPC_CServerOptions()->portNumber(8081);
//	server.getXMLRPC_CServerOptions()->uriPath("/RPC2");
//	server.getXMLRPCPP_ServerOptions()->setPort(8081);
	rpcselect.startServer();
	

}