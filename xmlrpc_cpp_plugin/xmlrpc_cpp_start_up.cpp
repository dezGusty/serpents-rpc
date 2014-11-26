#include "xmlrpc_cpp_start_up.h"
#include "implservermethod.h"
#include "servermanager.h"
#include <algorithm>
#include "xmlrpc_cpp_buildopts.h"
#include "xmlrpcpp_serveroptions.h"
#include "guslib\util\pluginmanager.h"

namespace serpents{
	class XMLRPCpp_StartUp::Impl{
		friend XMLRPCpp_StartUp;
		XmlRpc::XmlRpcServer* xmlServerPnt;
		std::thread controllThread;
		std::thread thrd;
		XMLRpcpp_ServerOptions serveroptions;
	};

	XMLRPCpp_StartUp::XMLRPCpp_StartUp(){
		Impl_ = new Impl;
	}
	XMLRPCpp_StartUp::~XMLRPCpp_StartUp(){
		delete Impl_;
	}

	std::thread& XMLRPCpp_StartUp::execute(Server* server){

		Impl_->controllThread = std::thread(&XMLRPCpp_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPCpp_StartUp::run, this, server);
		return Impl_->thrd;

	}
	ServerOptions* XMLRPCpp_StartUp::getImplServerOptions(){
		return &Impl_->serveroptions;
	}
	void XMLRPCpp_StartUp::run(Server* server){
		
		try {
			XmlRpc::XmlRpcServer s;
			FunctionRepository* fr = server->getRepository();

			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				XMLRPC_Method* b = new XMLRPC_Method(it->second, it->first, &s);
				s.addMethod(b);
			}

			s.bindAndListen(Impl_->serveroptions.getPortNumber());
		
			s.enableIntrospection(true);
			Impl_->xmlServerPnt = &s;

			//TODO: Figure out what that means
			s.work(-1.0);
		}
		catch (std::exception const& e) {
			std::cerr << "Something failed.  " << e.what() << std::endl;
		}
		

	}
	void XMLRPCpp_StartUp::controll(){
		
		std::cout << "Type \"exit\" to exit" << std::endl;

		bool keppAlive = true;
		bool isFirst = true;
		while (keppAlive){
			std::string command;
			if (Impl_->xmlServerPnt != nullptr){
				if (isFirst){
					std::cout << "server started" << std::endl;
					isFirst = false;
				}
				std::cin >> command;
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (strcmp(command.c_str(), "exit") == 0){
					Impl_->xmlServerPnt->shutdown();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}
		
	}
	void XMLRPCpp_StartUp::start(){
		Impl_->controllThread.join();
	}
	void XMLRPCpp_StartUp::stop(){}

	//Plugin overrides
	XMLRPCpp_StartUp* xmlrpc_cpp_plugin_Inst = nullptr;
	std::string hiddenName = "xmlrpcpp_plugin";

	const std::string& XMLRPCpp_StartUp::getName() const{
		return hiddenName;
	}
	void XMLRPCpp_StartUp::install(){
		ServerManager::get().registerServer(hiddenName, xmlrpc_cpp_plugin_Inst);

	}
	void XMLRPCpp_StartUp::initialize(){
		//ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);
	}
	void XMLRPCpp_StartUp::shutdown(){
	}
	void XMLRPCpp_StartUp::uninstall(){
		delete xmlrpc_cpp_plugin_Inst;
		xmlrpc_cpp_plugin_Inst = nullptr;
	}


	//-----------------------------------------------------------------------
	extern "C" void XMLRPC_CPP_EXPORT_SYMBOL dllStartPlugin(void)
	{
		// Create new plugin
		xmlrpc_cpp_plugin_Inst = new XMLRPCpp_StartUp();
		guslib::PluginManager::get().install(xmlrpc_cpp_plugin_Inst);

		// Register
	}
	extern "C" void XMLRPC_CPP_EXPORT_SYMBOL dllStopPlugin(void)
	{
		guslib::PluginManager::get().uninstall(xmlrpc_cpp_plugin_Inst);
		delete xmlrpc_cpp_plugin_Inst;
		xmlrpc_cpp_plugin_Inst = nullptr;
	}

}