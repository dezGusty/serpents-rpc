#ifndef XMLRPC_C_START_UP
#define XMLRPC_C_START_UP

#include "serpents\rpc\server\serverstartup.h"
#include "serpents\rpc\server\repository.h"
#include "xmlrpc-c\server_abyss.hpp"
#include "implservermethod.h"
#include "guslib\util\plugin.h"
namespace serpents {
	class  XMLRPC_C_StartUp : public ServerStartUp, public guslib::Plugin{
	private:
		class Impl;
		Impl* Impl_;
	public:
		XMLRPC_C_StartUp();
		XMLRPC_C_StartUp(const XMLRPC_C_StartUp&) = delete;
		~XMLRPC_C_StartUp();
		//ServerStartUp overrides
		virtual std::thread& execute(Server* server) override;
		virtual void run(Server* server) override;
		virtual void controll()override;
		virtual void start() override;
		virtual void stop() override;
		virtual ServerOptions* getImplServerOptions() override;

		//Plugin overrides
		virtual const std::string& getName() const override;
		virtual void install() override;
		virtual void initialize() override;
		virtual void shutdown() override;
		virtual void uninstall() override;

	};
}
#endif //XMLRPC_C_START_UP 