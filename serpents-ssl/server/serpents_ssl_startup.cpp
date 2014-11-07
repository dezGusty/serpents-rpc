//project libs
#include "serpents_ssl_startup.h"
#include "servermanager.h"
#include "serpents-rpc\serpents\rpc\server\server.h"
//guslibs
#include "guslib\util\pluginmanager.h"
#include "guslib\system\dynamiclibmanager.h"
#include <string>
#include <memory>

namespace serpents{
	SerpentsSSLStartUp* Inst;
	std::string hiddenName = "serpents_ssl";
	class SerpentsSSLStartUp::Impl{
		friend SerpentsSSLStartUp;
		ssl::server* server;
		std::thread thrd;
		std::thread controllThread;
	};
	SerpentsSSLStartUp::SerpentsSSLStartUp(){
		Impl_ = new Impl;
	}
	SerpentsSSLStartUp::~SerpentsSSLStartUp(){
		delete Impl_;
	}
	// server startUp overrides
	std::thread& SerpentsSSLStartUp::execute(Server* server){
		Impl_->controllThread = std::thread(&SerpentsSSLStartUp::controll, this);

		Impl_->thrd = std::thread(&SerpentsSSLStartUp::run, this, server);
		return Impl_->thrd;
	}
	void SerpentsSSLStartUp::controll(){
		std::cout << "Type \"exit\" to exit" << std::endl;
		bool keppAlive = true;
		bool isFirst = true;
		while (keppAlive){
			std::string command;
			if (Impl_->server != nullptr){
				if (isFirst){
					std::cout << "server started" << std::endl;
					isFirst = false;
				}
				std::cin >> command;
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
				if (strcmp(command.c_str(), "exit") == 0){
					this->Impl_->server->stop();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}
	}
	void SerpentsSSLStartUp::run(Server* server){
		START_LOGGING("type", "log.txt");
		boost::asio::io_service io_service;
		size_t numThreads = 3;
		Impl_->server = new serpents::ssl::server("localhost", io_service, 8080, numThreads);
		FunctionRepository* fr = server->getRepository();
		auto it = fr->getImpl()->methodContainer.begin();
		for (it; it != fr->getImpl()->methodContainer.end(); ++it){
			serpents::http::server2::sptr_method shrd = std::make_shared<serpents::Method*>(it->second);
			Impl_->server->getfunctionRepo().addServerMethod(shrd);
		}
		Impl_->server->run();
	}
	void SerpentsSSLStartUp::start(){
		Impl_->thrd.join();
	}
	void SerpentsSSLStartUp::stop(){
	}
	//Plugin overridesb
	const std::string& SerpentsSSLStartUp::getName() const{
		return hiddenName;
	}
	void SerpentsSSLStartUp::install() {
		ServerManager::getPtr()->registerServer(hiddenName, Inst);
	}
	void SerpentsSSLStartUp::initialize(){}
	void SerpentsSSLStartUp::shutdown() {}
	void SerpentsSSLStartUp::uninstall(){}

	//-----------------------------------------------------------------------
	extern "C" void SSLSERVER_EXPORT_SYMBOL dllStartPlugin(void)
	{
		// Create new plugin
		Inst = new SerpentsSSLStartUp();
		guslib::PluginManager::getPtr()->install(Inst);

	}
	extern "C" void SSLSERVER_EXPORT_SYMBOL dllStopPlugin(void)
	{
		guslib::PluginManager::getPtr()->uninstall(Inst);
		delete Inst;
		Inst = nullptr;
		
	}

}