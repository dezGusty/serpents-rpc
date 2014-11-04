

//system libs 
#include <mutex>
#include <algorithm>
// project libs 
#include "xmlrpc_c_startup.h"
#include "serpents\rpc\server\server.h"
#include "servermanager.h"
#include "..\xmlrpc_c_plugin\xmlrpc_c_buildopts.h"
#include "..\xmlrpc_c_plugin\implservermethod.h"
//guslibs
#include "guslib\util\pluginmanager.h"
#include "guslib\system\dynamiclibmanager.h"

#include "xmlrpc-c\server_abyss.h"
namespace serpents{
	XMLRPC_C_StartUp::XMLRPC_C_StartUp(){
		Impl_ = new Impl;
	}
	XMLRPC_C_StartUp::~XMLRPC_C_StartUp(){
		delete Impl_;
	}

	void XMLRPC_C_StartUp::run(Server* server){
		try {
			
			FunctionRepository* fr = server->getRepository();
			xmlrpc_c::registry myRegistry;
			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				xmlrpc_c::methodPtr const xmlRPCMEthodPtr(new XmlRPC_CMethod(it->second));
				myRegistry.addMethod(it->first, xmlRPCMEthodPtr);
				
			}
			//xmlrpc_c::serverAbyss::constrOpt conOpt = *server.getServerOptions()->getConstrOpt(); // TODO: FIX THIS
			xmlrpc_c::serverAbyss myAbyssServer(myRegistry);
			  //.registryP(&myRegistry)
			  //.portNumber(server.getPort()));
			this->serverAbyssPtr = &myAbyssServer; //change to set/get

			
			while (runCon){
				mtx.lock();
				myAbyssServer.runOnce();
				// xmlrpc_c::serverAbyss.run() never returns
				mtx.unlock();

			}
			

		}
		catch (std::exception const& e) {
			std::cerr << "Something failed.  " << e.what() << std::endl;
		}
	} //run()

	std::thread& XMLRPC_C_StartUp::execute(Server* server){
		Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this, server);
		return Impl_->thrd;
	} // (execute())

	void XMLRPC_C_StartUp::controll(){
		
		std::cout << "Type \"exit\" to exit" << std::endl;
		bool keppAlive = true;
		bool isFirst = true;
		while (keppAlive){
			std::string command;
			if (serverAbyssPtr != nullptr){
				if (isFirst){
					std::cout << "server started" << std::endl;
					isFirst = false;
				}
				std::cin >> command;
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (strcmp(command.c_str(), "exit") == 0){
					this->serverAbyssPtr->terminate();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}
		
	} //controll()

	void XMLRPC_C_StartUp::start(){
		runCon = true;
		  this->Impl_->controllThread.join();
	}
	void XMLRPC_C_StartUp::stop(){
		runCon = false;
	}

}


namespace serpents{
	XMLRPC_C_StartUp* xmlrpc_c_plugin_Inst = nullptr;
	std::string hiddenName = "xmlrpc_c_plugin";
	guslib::DynamicLib* dynamicLib;

	//Plugin overrides
	const std::string& XMLRPC_C_StartUp::getName() const{
		return hiddenName;
	}
	void XMLRPC_C_StartUp::install(){
		ServerManager::getPtr()->registerServer(hiddenName, xmlrpc_c_plugin_Inst);

	}
	void XMLRPC_C_StartUp::initialize(){
		ServerManager::getPtr()->registerServer(hiddenName, xmlrpc_c_plugin_Inst);
	}
	void XMLRPC_C_StartUp::shutdown(){
	}
	void XMLRPC_C_StartUp::uninstall(){
		delete xmlrpc_c_plugin_Inst;
		xmlrpc_c_plugin_Inst = nullptr;
	}


	//-----------------------------------------------------------------------
	extern "C" void PLUGINXMLRPC_C_EXPORT_SYMBOL dllStartPlugin(void)
	{
		// Create new plugin
		xmlrpc_c_plugin_Inst = new XMLRPC_C_StartUp();
		guslib::PluginManager::getPtr()->install(xmlrpc_c_plugin_Inst);

	}
	extern "C" void PLUGINXMLRPC_C_EXPORT_SYMBOL dllStopPlugin(void)
	{
		guslib::PluginManager::getPtr()->uninstall(xmlrpc_c_plugin_Inst);
		delete xmlrpc_c_plugin_Inst;
		xmlrpc_c_plugin_Inst = nullptr;
	}
}