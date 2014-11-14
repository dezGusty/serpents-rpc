#include "serpents\rpc\server\xmlrpc_cpp_start_up.h"
#include <algorithm>
namespace serpents{


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
		bool isFirst = true;
		while (keppAlive){
			std::string command;
			if (xmlServerPnt != nullptr){
				if (isFirst){
					std::cout << "server started" << std::endl;
					isFirst = false;
				}
				std::cin >> command;
				std::transform(command.begin(), command.end(), command.begin(), ::tolower);
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