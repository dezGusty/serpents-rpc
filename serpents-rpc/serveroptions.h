#ifndef SERVER_OPTIONS_H
#define SERVER_OPTIONS_H
#include "base.h"
#include "xmlrpc-c\server_abyss.hpp"
#ifdef SERPENTSDLL
#define SERVEROPT_EXPT _declspec(dllexport)
#else
#define SERVEROPT_EXPT _declspec(dllimport)
#endif
namespace serpents{
	class SERVEROPT_EXPT XMLRPC_CServerOptions{
		typedef xmlrpc_c::serverAbyss::constrOpt constrOpt;
	public:
		XMLRPC_CServerOptions();
		void portNumber(unsigned int   const& arg);
		void logFileName(std::string    const& arg);
		void keepaliveTimeout(unsigned int   const& arg);
		void keepaliveMaxConn(unsigned int   const& arg);
		void timeout(unsigned int   const& arg);
		void dontAdvertise(bool           const& arg);
		void uriPath(std::string    const& arg);
		void chunkResponse(bool           const& arg);
		void allowOrigin(std::string    const& arg);
		void accessCtlMaxAge(unsigned int const& arg);
		void serverOwnsSignals(bool           const& arg);
		void expectSigchld(bool           const& arg);
		constrOpt* getConstrOpt();
	private:
		constrOpt* constrOpt_;
	};

	class SERVEROPT_EXPT XMLRPCPP_ServerOptions{
		class Impl;
		Impl* Impl_;
	public:
		void setPort(unsigned int port);
		unsigned int getPort();
		XMLRPCPP_ServerOptions();
		~XMLRPCPP_ServerOptions();
	};
	class XMLRPCPP_ServerOptions::Impl{
		friend XMLRPCPP_ServerOptions;
		unsigned int portNum;
	};
}
#endif