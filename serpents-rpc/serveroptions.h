#ifndef SERVER_OPTIONS_H_
#define SERVER_OPTIONS_H_
#include "base.h"
#include <string>
#include "xmlrpc-c\server_abyss.hpp"
#ifdef SERPENTSDLL
#define SERVEROPT_DLL _declspec(dllexport)
#else
#define SERVEROPT_DLL _declspec(dllimport)
#endif
namespace serpents{
	class SERVEROPT_DLL XMLRPC_CServerOptions{
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

	class SERVEROPT_DLL XMLRPCPP_ServerOptions{
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
#endif  // SERVER_OPTIONS_H_