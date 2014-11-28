#ifndef SERPENTS_SSL_START_UP_H_
#define SERPENTS_SSL_START_UP_H_
#pragma once
#include "serpents\rpc\server\serverstartup.h"
#include "ssl_server_build_opts.h"
#include "guslib\util\plugin.h"
#include "serpents-ssl\server\server.hpp"
namespace serpents{
  class SerpentsSSLStartUp : public ServerStartUp, public guslib::Plugin{
  private:
    class Impl;
    Impl* Impl_;
  public:
    SerpentsSSLStartUp();
    SerpentsSSLStartUp(const SerpentsSSLStartUp&) = delete;
    ~SerpentsSSLStartUp();
    // server startUp overrides
    virtual std::thread& execute(Server* server) override;
    virtual void controll() override;
    virtual void run(Server* server) override;
    virtual void start() override;
    virtual void stop() override;
    virtual ServerOptions* getImplServerOptions() override;
    //Plugin overrides
    virtual const std::string& getName() const override;
    virtual void install() override;
    virtual void initialize() override;
    virtual void shutdown() override;
    virtual void uninstall() override;
  };
}
#endif 