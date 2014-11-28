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

#ifndef XMLRPC_C_SERVEROPTS_H_
#define XMLRPC_C_SERVEROPTS_H_

//  project libs
#include "xmlrpc-c\server_abyss.hpp"
#include "..\serpents-rpc\serpents\rpc\server\serveroptions.h"

//  system libs
#include <string>

namespace serpents
{
  class  XMLRPC_CServerOptions : public ServerOptions
  {
    typedef xmlrpc_c::serverAbyss::constrOpt constrOpt;

    public:
    XMLRPC_CServerOptions();
    ~XMLRPC_CServerOptions();
    XMLRPC_CServerOptions(const XMLRPC_CServerOptions&) = delete;

    void portNumber(unsigned int   const& arg) override;
    void logFileName(std::string    const& arg) override;
    void keepaliveTimeout(unsigned int   const& arg) override;
    void keepaliveMaxConn(unsigned int   const& arg) override;
    void timeout(unsigned int   const& arg) override;
    void dontAdvertise(bool           const& arg) override;
    void uriPath(std::string    const& arg) override;
    void chunkResponse(bool           const& arg) override;
    void allowOrigin(std::string    const& arg) override;
    void accessCtlMaxAge(unsigned int const& arg) override;
    void serverOwnsSignals(bool           const& arg) override;
    void expectSigchld(bool           const& arg) override;
    constrOpt* getConstrOpt();

  private:
    constrOpt* constrOpt_;
  };
}

#endif  //  XMLRPC_C_SERVEROPTS_H_

