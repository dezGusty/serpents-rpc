#ifndef XMLRPCPP_PLUGIN_H_
#define XMLRPCPP_PLUGIN_H_

#include "serpents\rpc\plugin.h"
#include "serpents\rpc\server\serverstartup.h"
#include ""
#include "guslib\system\dynamiclibmanager.h"
namespace serpents{
	class XMLRPC_CPP_Plugin : public ServerStartUp,
		public IPlugin
	{
	public:
		XMLRPC_CPP_Plugin(){}
		~XMLRPC_CPP_Plugin(){}
		//ServerStartUp overrides
		virtual std::thread& execute(Server& server) override;
		virtual void run(Server& server) override;

		//IPlugin overrides
		virtual const std::string& getName() const override;
		virtual void install() override;
		virtual void initialise() override;
		virtual void shutdown() override;
		virtual void uninstall() override;
	private:
		xmlrpc_c::serverAbyss* serverAbyssPtr;
	};
}

#endif XMLRPCPP_PLUGIN_H_