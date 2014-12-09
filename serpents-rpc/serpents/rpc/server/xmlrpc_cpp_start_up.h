#ifndef XMLRPC_CPP_START_UP_H_
#define XMLRPC_CPP_START_UP_H_
#include "guslib\util\plugin.h"
#include "..\build\ServerManager\servermanager.h"

#include "guslib\system\dynamiclibmanager.h"
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
#ifndef XMLRPC_C_PLUGIN_H_
#define XMLRPC_C_PLUGIN_H_


	namespace serpents{
		class XMLRPC_C_Plugin : public ServerStartUp,
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
}

#endif // XMLRPC_CPP_START_UP_H_