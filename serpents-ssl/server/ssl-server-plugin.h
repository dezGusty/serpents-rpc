#ifndef SSL_SERVER_PLUGIN_H_
#define SSL_SERVER_PLUGIN_H_
#include "plugin.h"
#include "server\server.hpp"
namespace serpents{
	class SSL_Server_Plugin : public IPlugin {
	public:
		SSL_Server_Plugin();
		~SSL_Server_Plugin();

		const std::string& getName() const;

		void install();

		void initialise();

		void shutdown();

		void uninstall();
	protected:
		ssl::server* server;
	};

}
#endif // SSL_SERVER_PLUGIN_H_