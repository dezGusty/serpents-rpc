#ifndef XMLRPC_CPP_START_UP_H_
#define XMLRPC_CPP_START_UP_H_
#include "serpents\rpc\server\serverstartup.h"
#include "xmlrpc++\XmlRpc.h"
#include "serpents\rpc\server\implservermethod.h"
#include "serpents\rpc\server\server.h"
namespace serpents{

	class  XMLRPCpp_StartUp : public ServerStartUp{
	public:
		XmlRpc::XmlRpcServer* xmlServerPnt;
		std::thread& execute(Server& server);
		void controll();
		void run(Server& server);

	};
}

#endif // XMLRPC_CPP_START_UP_H_