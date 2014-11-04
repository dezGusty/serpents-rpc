

//system libs 
#include <mutex>
#include <algorithm>
// project libs 
#include "xmlrpc_c_startup.h"
#include "serpents\rpc\server\server.h"


namespace serpents{

	void XMLRPC_C_StartUp::run(Server& server){
		try {

			FunctionRepository* fr = server.getRepository();
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
			//this->serverAbyssPtr = &myAbyssServer; //change to set/get

			std::mutex mtx;
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

	std::thread& XMLRPC_C_StartUp::execute(Server& server){
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
}