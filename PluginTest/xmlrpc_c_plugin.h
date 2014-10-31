#ifndef XMLRPC_C_PLUGIN_H_
#define XMLRPC_C_PLUGIN_H_

#include "guslib\util\plugin.h"
#include "serpents\rpc\server\serverstartup.h"
#include "servermanager.h"
#include "xmlrpc_plug_in_opts.h"
#include "guslib\system\dynamiclibmanager.h"
namespace serpents{
	class XMLRPC_C_Plugin : public XMLRPCpp_StartUp, 
						public guslib::Plugin
	{
	public:
		//ServerStartUp overrides
		virtual std::thread& execute(Server& server) override;
		virtual void run(Server& server) override;

		//Plugin overrides
		virtual const std::string& getName() const override;
		virtual void install() override;
		virtual void initialize() override;
		virtual void shutdown() override;
		virtual void uninstall() override;
	private:
		
	};
}

#endif XMLRPC_C_PLUGIN_H_