#include "serverstartup.h"
namespace serpents{
	void ServerStartUp::start(){
		this->Impl_->controllThread.join();

	}
	ServerStartUp::ServerStartUp(){
		Impl_ = new Impl();
	}
	void XMLRPC_C_StartUp::run(Server& server){
		try {

			FunctionRepository* fr = server.getRepository();
			xmlrpc_c::registry myRegistry;
			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				xmlrpc_c::methodPtr const xmlRPCMEthodPtr(new XmlRPC_CMethod(it->second));
				myRegistry.addMethod(it->first, xmlRPCMEthodPtr);
			}
			xmlrpc_c::serverAbyss::constrOpt conOpt = *server.getXMLRPC_CServerOptions()->getConstrOpt();
			xmlrpc_c::serverAbyss myAbyssServer(conOpt.registryP(&myRegistry));
			//	.registryP(&myRegistry)
			//	.portNumber(server.getPort()));
			this->serverAbyssPtr = &myAbyssServer; //change to set/get

			while (runCon){
				myAbyssServer.runOnce();
				// xmlrpc_c::serverAbyss.run() never returns

			}

		}
		catch (std::exception const& e) {
			std::cerr << "Something failed.  " << e.what() << std::endl;
		}
	}



	std::thread& XMLRPC_C_StartUp::execute(Server& server){
		Impl_->controllThread = std::thread(&XMLRPC_C_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPC_C_StartUp::run, this, server);
		return Impl_->thrd;
	}

	void XMLRPC_C_StartUp::controll(){
		std::cout << "Type \"exit\" to exit" << std::endl;
		bool keppAlive = true;
		std::chrono::milliseconds dura(20);
		while (keppAlive){
			std::string command;
			if (serverAbyssPtr != nullptr){

				std::cin >> command;
				if (strcmp(command.c_str(), "exit") == 0){
					this->serverAbyssPtr->terminate();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}

	}

	std::thread& XMLRPCpp_StartUp::execute(Server& server){

		Impl_->controllThread = std::thread(&XMLRPCpp_StartUp::controll, this);

		Impl_->thrd = std::thread(&XMLRPCpp_StartUp::run, this, server);
		return Impl_->thrd;

	}

	void XMLRPCpp_StartUp::run(Server& server){

		try {
			XmlRpc::XmlRpcServer s;
			FunctionRepository* fr = server.getRepository();

			std::map<std::string, Method *>::iterator it;
			for (it = fr->getImpl()->methodContainer.begin(); it != fr->getImpl()->methodContainer.end(); ++it){
				XMLRPC_Method* b = new XMLRPC_Method(it->second, it->first, &s);
				s.addMethod(b);
			}

			s.bindAndListen(8081);
			s.enableIntrospection(true);
			xmlServerPnt = &s;
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
		std::chrono::milliseconds dura(20);
		while (keppAlive){
			std::string command;
			if (xmlServerPnt != nullptr){

				std::cin >> command;
				if (strcmp(command.c_str(), "exit") == 0){
					this->xmlServerPnt->shutdown();
					std::cout << "server closed" << std::endl;
					keppAlive = false;
				}

			}
			std::this_thread::yield();
		}


	}

}