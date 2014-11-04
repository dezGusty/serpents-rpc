#ifndef XMLRPC_C_START_UP
#define XMLRPC_C_START_UP

#include "serpents\rpc\server\serverstartup.h"
#include "serpents\rpc\server\repository.h"
#include "xmlrpc-c\server_abyss.h"
#include "serpents\rpc\server\implservermethod.h"
namespace serpents {
	class  XMLRPC_C_StartUp : public ServerStartUp{
	public:
		xmlrpc_c::serverAbyss* serverAbyssPtr;
		std::thread& execute(Server& server);
		void controll();
		void run(Server& server);

	};
}
#endif //XMLRPC_C_START_UP 
