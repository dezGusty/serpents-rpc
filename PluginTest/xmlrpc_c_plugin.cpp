#include "xmlrpc_c_plugin.h"
#include "serpents/rpc/server/implservermethod.h"
#include "guslib\util\pluginmanager.h"

namespace serpents{
	XMLRPC_C_Plugin* xmlrpc_c_plugin_Inst = nullptr;
	std::string hiddenName = "xmlrpc_plugin";
	guslib::DynamicLib* dynamicLib;

	//
	//ServerStartUp overrides
	void XMLRPC_C_Plugin::run(Server& server){
		XMLRPCpp_StartUp::run(server);
	}



	std::thread& XMLRPC_C_Plugin::execute(Server& server){
		return XMLRPCpp_StartUp::execute(server);
	}


	//IPlugin overrides
	const std::string& XMLRPC_C_Plugin::getName() const{
		return hiddenName;
	}
	void XMLRPC_C_Plugin::install(){
		guslib::PluginManager::get().install(xmlrpc_c_plugin_Inst);
		
	}
	void XMLRPC_C_Plugin::initialize(){
		ServerManager::get().registerServer(hiddenName, xmlrpc_c_plugin_Inst);
	}
	void XMLRPC_C_Plugin::shutdown(){
	}
	void XMLRPC_C_Plugin::uninstall(){
		delete xmlrpc_c_plugin_Inst;
		xmlrpc_c_plugin_Inst = nullptr;
	}


	//-----------------------------------------------------------------------
	extern "C" void XMLRPC_C_PLUGIN_EXPORT_SYMBOL dllStartPlugin(void)
	{
		// Create new plugin
		xmlrpc_c_plugin_Inst = new XMLRPC_C_Plugin();
		guslib::PluginManager::get().install(xmlrpc_c_plugin_Inst);
	
		// Register
	}
	extern "C" void XMLRPC_C_PLUGIN_EXPORT_SYMBOL dllStopPlugin(void)
	{
		guslib::PluginManager::get().uninstall(xmlrpc_c_plugin_Inst);
		delete xmlrpc_c_plugin_Inst;
		xmlrpc_c_plugin_Inst = nullptr;
	}
}