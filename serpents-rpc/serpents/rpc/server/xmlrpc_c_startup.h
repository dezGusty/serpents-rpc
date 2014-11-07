#ifndef XMLRPC_C_START_UP
#define XMLRPC_C_START_UP

#include "serpents\rpc\server\serverstartup.h"
#include "serpents\rpc\server\repository.h"
#include "xmlrpc-c\server_abyss.hpp"
#include "serpents\rpc\server\implservermethod.h"
#include "guslib\util\plugin.h"
namespace serpents {
	
	class  XMLRPC_C_StartUp : public ServerStartUp, public guslib::Plugin{
		class Impl;
		Impl* Impl_;
		std::mutex mtx;
		XMLRPC_C_StartUp(const XMLRPC_C_StartUp& copy){}
	public:
		bool runCon = true;;
		xmlrpc_c::serverAbyss* serverAbyssPtr;
		XMLRPC_C_StartUp();
		~XMLRPC_C_StartUp();
		// server startUp overrides
		virtual std::thread& execute(Server* server) override;
		virtual void controll() override;
		virtual void run(Server* server) override;
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
#endif //XMLRPC_C_START_UP 
