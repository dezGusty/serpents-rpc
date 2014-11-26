#include "xmlrpc_c_serveroptions.h"

namespace serpents{
	//initiaize xmlrpc_c specific server opt with port 8080
	XMLRPC_CServerOptions::XMLRPC_CServerOptions(){
		constrOpt_ = new constrOpt();
		constrOpt_->portNumber(8080);
	}
	XMLRPC_CServerOptions::~XMLRPC_CServerOptions(){
		delete constrOpt_;
	}
	void XMLRPC_CServerOptions::portNumber(unsigned int const& arg){
		constrOpt_->portNumber(arg);
	}
	void  XMLRPC_CServerOptions::logFileName(std::string    const& arg){
		constrOpt_->logFileName(arg);
	}
	void  XMLRPC_CServerOptions::keepaliveTimeout(unsigned int   const& arg){
		constrOpt_->keepaliveTimeout(arg);
	}
	void XMLRPC_CServerOptions::keepaliveMaxConn(unsigned int   const& arg){
		constrOpt_->keepaliveMaxConn(arg);
	}
	void XMLRPC_CServerOptions::timeout(unsigned int   const& arg){
		constrOpt_->timeout(arg);
	}
	void XMLRPC_CServerOptions::dontAdvertise(bool           const& arg){
		constrOpt_->dontAdvertise(arg);
	}
	void XMLRPC_CServerOptions::uriPath(std::string    const& arg){
		constrOpt_->uriPath(arg);
	}
	void XMLRPC_CServerOptions::chunkResponse(bool const& arg){
		constrOpt_->chunkResponse(arg);
	}
	void XMLRPC_CServerOptions::allowOrigin(std::string    const& arg){
		constrOpt_->allowOrigin(arg);
	}
	void XMLRPC_CServerOptions::accessCtlMaxAge(unsigned int const& arg){
		constrOpt_->accessCtlMaxAge(arg);
	}
	void XMLRPC_CServerOptions::serverOwnsSignals(bool const& arg){
		constrOpt_->serverOwnsSignals(arg);
	}
	void XMLRPC_CServerOptions::expectSigchld(bool const& arg){
		constrOpt_->expectSigchld(arg);
	}
	xmlrpc_c::serverAbyss::constrOpt* XMLRPC_CServerOptions::getConstrOpt(){
		return this->constrOpt_;
	}
}