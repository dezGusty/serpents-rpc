// system libs
#include <mutex>
#include <algorithm>
// project libs 
#include "xmlrpc_c_startup.h"
#include "serpents\rpc\server\server.h"
#include "guslib\util\pluginmanager.h"
#include "servermanager.h"
#include "xmlrpc_c_serveroptions.h"
#include "xmlrpc_c_buildopts.h"
namespace serpents{
	class XMLRPC_C_StartUp::Impl{
		friend XMLRPC_C_StartUp;
		std::thread controllThread;
		std::thread thrd;
		//std::mutex mtx;
		xmlrpc_c::serverAbyss* serverAbyssPtr;
		bool runCon;
		xmlrpc_c::registry myRegistry;
		XMLRPC_CServerOptions serveroptions;
	};

	XMLRPC_C_StartUp::XMLRPC_C_StartUp(){
		Impl_ = new Impl;
	}
	XMLRPC_C_StartUp::~XMLRPC_C_StartUp(){
		delete Impl_;
	}
	ServerOptions* XMLRPC_C_StartUp::getImplServerOptions(){
		return &Impl_->serveroptions;
	}

	void XMLRPC_C_StartUp::run(serpents::Server* server){
		try {

			FunctionRepository* fr = server->getRepository();
			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				//xmlrpc_c::methodPtr const xmlRPCMEthodPtr();
				//Impl_->mtx.lock();
				Impl_->myRegistry.addMethod(it->first, new XmlRPC_CMethod(it->second));
				//Impl_->mtx.unlock();
			}
			//xmlrpc_c::serverAbyss::constrOpt conOpt = *server.getServerOptions()->getConstrOpt(); // TODO: FIX THIS
			Impl_->serveroptions.getConstrOpt()->registryP(&Impl_->myRegistry);
			xmlrpc_c::serverAbyss myAbyssServer(*Impl_->serveroptions.getConstrOpt());
		
			Impl_->serverAbyssPtr = &myAbyssServer; //change to set/get

			std::mutex mtx;
			while (Impl_->runCon){
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

	std::thread& XMLRPC_C_StartUp::execute(serpents::Server* server){
		Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this, server);
		return Impl_->thrd;
	} // (execute())

	void XMLRPC_C_StartUp::start(){
		Impl_->controllThread.join();
	}
	void XMLRPC_C_StartUp::stop(){

	}
	void XMLRPC_C_StartUp::controll(){
		std::cout << "Type \"exit\" to exit" << std::endl;
		bool keppAlive = true;
		bool isFirst = true;
		while (keppAlive){
			std::string command;
			if (Impl_->serverAbyssPtr != nullptr){
				if (isFirst){
					std::cout << "server started" << std::endl;
					isFirst = false;
				}
				std::cin >> command;
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (strcmp(command.c_str(), "exit") == 0){
					Impl_->serverAbyssPtr->terminate();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}

	} //controll()


	//Plugin overrides
	XMLRPC_C_StartUp* xmlrpc_c_plugin_Inst = nullptr;
	std::string hiddenName = "xmlrpc_plugin";
	
	const std::string& XMLRPC_C_StartUp::getName() const{
		return hiddenName;
	}
	void XMLRPC_C_StartUp::install(){
		ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);

	}
	void XMLRPC_C_StartUp::initialize(){
		//ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);
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
		guslib::PluginManager::get().install(xmlrpc_c_plugin_Inst);

		// Register
	}
	extern "C" void PLUGINXMLRPC_C_EXPORT_SYMBOL dllStopPlugin(void)
	{
		guslib::PluginManager::get().uninstall(xmlrpc_c_plugin_Inst);
		delete xmlrpc_c_plugin_Inst;
		xmlrpc_c_plugin_Inst = nullptr;
	}
}