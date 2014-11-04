#include <iostream>
#include <string>
#include "guslib\system\dynamiclib.h"
#include "guslib\system\dynamiclibmanager.h"
#include "guslib/common/simpleexception.h"
#include "..\build\ServerManager\servermanager.h"
#include "serpents\rpc\server\repository.h"
#include "serpents\rpc\server\server.h"
#include "serpents\rpc\server\rpcselector.h"


void loadPlugin(const std::string& pluginName)
{
	guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStartPlugin");

	if (!pFunc)
	{
		throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
	}

	// This must call installPlugin
	pFunc();
}

void unloadPlugin(const std::string& pluginName)
{
	guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStopPlugin");

	if (!pFunc)
	{
		throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
	}

	// This must call installPlugin
	pFunc();
}
class RPCMethod2 :public  serpents::Method{
public:
	RPCMethod2(){

		setSignature(std::string("i:ii"));
		setHelp(std::string("this method adds two ints together"));
		setName("add");
	}
	void execute(serpents::ParameterContainer* parameters, RetValue* rv){
		int sum = 0;
		sum = parameters->getInt(0) + parameters->getInt(1);
		rv->setValue(sum);
	}

};

void main(){
	try{
		RPCMethod2* rpcm = new RPCMethod2();
		serpents::FunctionRepository fr;
		fr.addMethod(rpcm);
		std::string plugin_name("xmlrpc_c_plugin.dll");



		serpents::Server s;
		s.setRepository(fr);

		serpents::RPCSelector rpcselect;
		rpcselect.selectRPCMethod(s, plugin_name);
	}
	catch (std::exception e){
		std::cerr << e.what() << std::endl;
	}
	

}