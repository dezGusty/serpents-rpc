#include "xmlrpcpp_serveroptions.h"

namespace serpents{
  class XMLRpcpp_ServerOptions::Impl{
    friend XMLRpcpp_ServerOptions;
    std::string uri;
    int port;
  };
  void XMLRpcpp_ServerOptions::uriPath(std::string    const& arg){
    Impl_->uri = arg;
  }
  void XMLRpcpp_ServerOptions::portNumber(unsigned int   const& arg){
    Impl_->port = arg;
  }
  XMLRpcpp_ServerOptions::XMLRpcpp_ServerOptions(){
    Impl_ = new Impl;
  }
  XMLRpcpp_ServerOptions::~XMLRpcpp_ServerOptions(){
    delete Impl_;
  }
  int XMLRpcpp_ServerOptions::getPortNumber(){
    return Impl_->port;
  }
  std::string& XMLRpcpp_ServerOptions::getUri(){
    return Impl_->uri;
  }
}