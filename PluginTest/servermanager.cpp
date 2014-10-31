#include "servermanager.h"


namespace serpents{
	void ServerManagerUtil::registerServer(const std::string name, ServerStartUp* server){
		registeredServer_[name] = server;
	}
	void ServerManagerUtil::unregisterServer(const std::string name, ServerStartUp* server){
		auto it = registeredServer_.find(name);
		if (it!=registeredServer_.end()){
			registeredServer_.erase(it);
		}
	}
	ServerStartUp* ServerManagerUtil::getServerPointer(const std::string name){
		auto it = registeredServer_.find(name);
		if (it != registeredServer_.end()){
			return it->second;
		}
		else{
			return nullptr;
		}

	}

}