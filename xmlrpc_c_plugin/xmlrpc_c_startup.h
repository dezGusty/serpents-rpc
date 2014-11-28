//   This file is part of the serpents-rpc library, licensed under the terms of the MIT License.
//
//   The MIT License
//   Copyright (C) 2010-2014  The serpents-rpc team (See AUTHORS file)
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in
//   all copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//   THE SOFTWARE.

#ifndef XMLRPC_C_START_UP_H_
#define XMLRPC_C_START_UP_H_

//  system libs
#include <string>

//  project libs
#include "serpents\rpc\server\serverstartup.h"
#include "serpents\rpc\server\repository.h"
#include "xmlrpc-c\server_abyss.hpp"
#include "implservermethod.h"

//  guslibs
#include "guslib\util\plugin.h"
namespace serpents
{
  class  XMLRPC_C_StartUp : public ServerStartUp, public guslib::Plugin
  {
    private:
    class Impl;
    Impl* Impl_;
    public:
    XMLRPC_C_StartUp();
    XMLRPC_C_StartUp(const XMLRPC_C_StartUp&) = delete;
    ~XMLRPC_C_StartUp();
    //  ServerStartUp overrides
    virtual std::thread& execute(Server* server) override;
    virtual void run(Server* server) override;
    virtual void controll()override;
    virtual void start() override;
    virtual void stop() override;
    virtual ServerOptions* getImplServerOptions() override;

    //  Plugin overrides
    virtual const std::string& getName() const override;
    virtual void install() override;
    virtual void initialize() override;
    virtual void shutdown() override;
    virtual void uninstall() override;
  };
}
#endif  //  XMLRPC_C_START_UP_H_

