#include <iostream>
#include <string>
#include "guslib\system\dynamiclib.h"
#include "guslib\system\dynamiclibmanager.h"
#include "guslib/common/simpleexception.h"

#include "servermanager.h"

void loadPlugin(const std::string& pluginName)
{
	guslib::DynamicLib* lib = guslib::DynamicLibManager::get().load(pluginName);

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStartPlugin");

	if (!pFunc)
	{
		throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
	}

	// This must call installPlugin
	pFunc();
}

void unloadPlugin(const std::string& pluginName)
{
	guslib::DynamicLib* lib = guslib::DynamicLibManager::get().load(pluginName);

	DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStopPlugin");

	if (!pFunc)
	{
		throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
	}

	// This must call installPlugin
	pFunc();
}


void main(){
	std::cout << "start" << std::endl;
	std::string plugin_name("serpents-rpc.dll");

	std::cout << "loading plugin: " << plugin_name << std::endl;
	loadPlugin(plugin_name);
	std::cout << "loaded plugin: " << plugin_name << std::endl;

}