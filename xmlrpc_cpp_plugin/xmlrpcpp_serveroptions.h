#ifndef XMLRPC_SERVEROPTS_H_
#define XMLRPC_SERVEROPTS_H_
#include "serpents\rpc\server\serveroptions.h"

namespace serpents{
	class XMLRpcpp_ServerOptions : public ServerOptions{
	private: 
		class Impl;
		Impl* Impl_;
	public:
		XMLRpcpp_ServerOptions();
		~XMLRpcpp_ServerOptions();
		virtual void portNumber(unsigned int   const& arg);
		//method to access xmlrpc_c's logger. Only availible if the option
		//is selected when buidling xmlrpc_c, if not it does nothing.
		virtual void logFileName(std::string    const& arg){}
		virtual void keepaliveTimeout(unsigned int   const& arg){}
		virtual void keepaliveMaxConn(unsigned int   const& arg){}
		virtual void timeout(unsigned int   const& arg) {}
		virtual void dontAdvertise(bool           const& arg) {}
		virtual void uriPath(std::string    const& arg);
		virtual void chunkResponse(bool           const& arg) {}
		virtual void allowOrigin(std::string    const& arg){}
		virtual void accessCtlMaxAge(unsigned int const& arg){}
		virtual void serverOwnsSignals(bool           const& arg) {}
		virtual void expectSigchld(bool           const& arg) {}
		int getPortNumber();
		std::string& getUri();
	};
}

#endif 