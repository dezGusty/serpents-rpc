#ifndef SERPENTS_SSL_SERVEROPTS_H_
#define SERPENTS_SSL_SERVEROPTS_H_

#include "serpents\rpc\server\serveroptions.h"
namespace serpents{
  class SSL_ServerOptions : public ServerOptions{
  private:
    class Impl;
    Impl* Impl_;
  public:
    SSL_ServerOptions();
    ~SSL_ServerOptions();
    SSL_ServerOptions(const SSL_ServerOptions&) = delete;
    virtual void portNumber(unsigned int   const& arg);
    //sets the log file for serpents' logger if USELOG4CPP is define
    //does not set te log file for the underlying libs' logger
    virtual void logFileName(std::string    const& arg);
    virtual void uriPath(std::string    const& arg);

    std::string& getLogFileName();
    std::string& getUriPath();
    int getPortNumber();

    //  placeholder methods 
    virtual void keepaliveTimeout(unsigned int   const& arg){}
    virtual void keepaliveMaxConn(unsigned int   const& arg){}
    virtual void timeout(unsigned int   const& arg) {}
    virtual void dontAdvertise(bool           const& arg) {}
    virtual void chunkResponse(bool           const& arg){}
    virtual void allowOrigin(std::string    const& arg) {}
    virtual void accessCtlMaxAge(unsigned int const& arg) {}
    virtual void serverOwnsSignals(bool           const& arg) {}
    virtual void expectSigchld(bool           const& arg) {}
    
  };
}

#endif SERPENTS_SSL_SERVEROPTS_H_