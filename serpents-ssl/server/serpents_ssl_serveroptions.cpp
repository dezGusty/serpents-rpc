#include "serpents-ssl\server\serpents_ssl_serveroptions.h"

namespace serpents{
  class SSL_ServerOptions::Impl{
    friend SSL_ServerOptions;
    std::string logFileName;
    std::string uriPath;
    int portNumber;
  };

  SSL_ServerOptions::SSL_ServerOptions(){
    Impl_ = new Impl;
  }
  SSL_ServerOptions::~SSL_ServerOptions(){
    delete Impl_;
  }
  void SSL_ServerOptions::portNumber(unsigned int   const& arg){
    Impl_->portNumber = arg;
  }
  void SSL_ServerOptions::logFileName(std::string    const& arg){
    Impl_->logFileName=arg;
  }
  void SSL_ServerOptions::uriPath(std::string    const& arg){
    Impl_->uriPath=arg;
  }

  std::string& SSL_ServerOptions::getLogFileName() {
    return Impl_->logFileName;
  }
  std::string& SSL_ServerOptions::getUriPath(){
    return Impl_->uriPath;
  }
  int SSL_ServerOptions::getPortNumber(){
    return Impl_->portNumber;
  }
}