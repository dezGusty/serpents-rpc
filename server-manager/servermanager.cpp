#include "servermanager.h"
#include "iostream"

namespace serpents{
  class ServerManagerUtil::Impl{
    friend ServerManagerUtil;
    static std::map<std::string, ServerStartUp*>* getServerMap(){
      static std::map<std::string, ServerStartUp*> registeredServer_;
      return &registeredServer_;
    }
    
  };
  ServerManagerUtil::ServerManagerUtil(){
    Impl_ = new Impl;
  }
  ServerManagerUtil::~ServerManagerUtil(){
    delete Impl_;
  }
  void ServerManagerUtil::registerServer(const std::string name, ServerStartUp* server){
    Impl::getServerMap()->insert(std::pair<std::string, ServerStartUp*>(name, server));
  }
  void ServerManagerUtil::unregisterServer(const std::string name, ServerStartUp* server){
    auto it = Impl::getServerMap()->find(name);
    if (it != Impl::getServerMap()->end()){
      Impl_->Impl::getServerMap()->erase(it);
    }
  }
  ServerStartUp* ServerManagerUtil::getServerPointer(const std::string& name){
    std::cout << Impl::getServerMap()->size() << std::endl;
    auto it = Impl::getServerMap()->find(name);
    if (it != Impl::getServerMap()->end()){
      return it->second;
    }
    else{
      return nullptr;
    }

  }

}