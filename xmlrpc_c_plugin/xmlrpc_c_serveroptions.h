#ifndef XMLRPC_C_SERVEROPTS_H_
#define XMLRPC_C_SERVEROPTS_H_

#include "xmlrpc-c\server_abyss.hpp"
#include "..\serpents-rpc\serpents\rpc\server\serveroptions.h"
namespace serpents{
	class  XMLRPC_CServerOptions : public ServerOptions{
		typedef xmlrpc_c::serverAbyss::constrOpt constrOpt;
		
	public:
		XMLRPC_CServerOptions();
		~XMLRPC_CServerOptions();
		XMLRPC_CServerOptions(const XMLRPC_CServerOptions&) = delete;

		void portNumber(unsigned int   const& arg) override;
		void logFileName(std::string    const& arg) override;
		void keepaliveTimeout(unsigned int   const& arg) override;
		void keepaliveMaxConn(unsigned int   const& arg) override;
		void timeout(unsigned int   const& arg) override;
		void dontAdvertise(bool           const& arg) override;
		void uriPath(std::string    const& arg) override;
		void chunkResponse(bool           const& arg) override;
		void allowOrigin(std::string    const& arg) override;
		void accessCtlMaxAge(unsigned int const& arg) override;
		void serverOwnsSignals(bool           const& arg) override;
		void expectSigchld(bool           const& arg) override;
		constrOpt* getConstrOpt();
	private:
		constrOpt* constrOpt_;
	};
}

#endif //XMLRPC_C_SERVEROPTS_H_