
//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#include "RPCSelector.h"
#include "guslib\system\dynamiclib.h"
#include "guslib\system\dynamiclibmanager.h"
#include "guslib/common/simpleexception.h"
#include "servermanager.h"
#include "serpents\rpc\server\rpcselector.h"
#include "serpents\rpc\server\server.h"
namespace serpents{
	void loadPlugin(const std::string& pluginName)
	{
		guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

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
		guslib::DynamicLib* lib = guslib::DynamicLibManager::getPtr()->load(pluginName);

		DLL_START_PLUGIN pFunc = (DLL_START_PLUGIN)lib->getSymbol("dllStopPlugin");

		if (!pFunc)
		{
			throw new guslib::SimpleException("Cannot find symbol dllStartPlugin in library ");
		}

		// This must call installPlugin
		pFunc();
	}

	//plug in

	//choose impl of server 
	void RPCSelector::selectRPCMethod(Server& server, std::string method){
		server_ = &server;

		std::cout << "start" << std::endl;
		std::string plugin_name("xmlrpc_c_plugin.dll");
		std::string ssl_plugin_name("serpents_ssl.dll");
		std::cout << "loading plugin: " << plugin_name << std::endl;
		loadPlugin(plugin_name);
		std::cout << "loaded plugin: " << plugin_name << std::endl;
		std::cout << "loading plugin: " << ssl_plugin_name << std::endl;
		loadPlugin(ssl_plugin_name);
		std::cout << "loaded plugin: " << ssl_plugin_name << std::endl;

		this->ServerStartUpImpl_ = serpents::ServerManager::getPtr()->getServerPointer(method);
		if (ServerStartUpImpl_ == nullptr)
			throw std::exception("no plugin loaded");
#ifdef USE_LOG4CPP
		auto map = server_->getLogTargets();
		for (auto it = map->begin(); it != map->end(); ++it){
			Log::getPtr()->addAppender(it->second, it->first);
		}
		Log::getPtr()->info("---using library " + method + "---");
#endif

	}
	void RPCSelector::stopServer(){
		// ServerStartUpImpl_->runCon = false;
	}

	void RPCSelector::startServer(){
		ServerStartUpImpl_->execute(server_);
		ServerStartUpImpl_->start();
	}
	RPCSelector::RPCSelector()
	{
	}


	RPCSelector::~RPCSelector()
	{
		delete ServerStartUpImpl_;

	}


}
