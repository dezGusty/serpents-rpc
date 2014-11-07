#include "ssl-server-plugin.h"



namespace serpents{
	const std::string PluginName = "ssl-server";
	guslib::DynamicLibManager dynamicLibManager;
	guslib::DynamicLib* dynamicLib;
	SSL_Server_Plugin::SSL_Server_Plugin(){
		server = nullptr;
	}
	SSL_Server_Plugin::~SSL_Server_Plugin(){
		delete server;
	}
	const std::string& SSL_Server_Plugin::getName() const{
		return PluginName;
	}

	void SSL_Server_Plugin::install(){
		dynamicLib =dynamicLibManager.getPtr()->load("ssl-server.dll");
	}

	void SSL_Server_Plugin::uninstall(){
		dynamicLibManager.getPtr()->unload(dynamicLib);
	}

	void SSL_Server_Plugin::initialise()
	{
		// does nothing
	}

	void SSL_Server_Plugin::shutdown()
	{
		// does nothing
	}
	

}