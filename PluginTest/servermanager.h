#ifndef SERVER_MANAGER_H_
#define SERVER_MANAGER_H_
#include <map>

#include "guslib/common/singleton.hpp"
#include "serpents\rpc\server\serverstartup.h"
#include "servermanager_build_opts.h"
namespace serpents{
	class SERVERMGR_EXPORT_SYMBOL ServerManagerUtil{
	private:
		std::map<std::string, ServerStartUp*> registeredServer_;
	public:
		void registerServer(const std::string name, ServerStartUp* server);
		void unregisterServer(const std::string name, ServerStartUp* server);
		ServerStartUp* getServerPointer(const std::string name);
	};
	typedef guslib::Singleton<ServerManagerUtil> ServerManager;
	SERVERMGR_EXPIMP_TEMPLATE template class SERVERMGR_EXPORT_SYMBOL guslib::Singleton <ServerManagerUtil>;
}


#endif SERVER_MANAGER_H_