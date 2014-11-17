#ifndef XMLRPC_CPP_START_UP_H_
#define XMLRPC_CPP_START_UP_H_
#include "serpents\rpc\server\serverstartup.h"
#include "xmlrpc++\XmlRpc.h"
#include "serpents\rpc\server\implservermethod.h"
#include "serpents\rpc\server\server.h"
#include "guslib\util\plugin.h"
#include "xmlrpc++\XmlRpc.h"
namespace serpents{

	class  XMLRPCpp_StartUp : public ServerStartUp, public guslib::Plugin{
	private:
		class Impl;
		Impl* Impl_;
	public:
		XMLRPCpp_StartUp();
		~XMLRPCpp_StartUp();
		virtual std::thread& execute(Server* server) override;
		virtual void run(Server* server) override;
		virtual void controll()override;
		virtual void start() override;
		virtual void stop() override;

		//Plugin overrides
		virtual const std::string& getName() const override;
		virtual void install() override;
		virtual void initialize() override;
		virtual void shutdown() override;
		virtual void uninstall() override;

	};
}

#endif // XMLRPC_CPP_START_UP_H_