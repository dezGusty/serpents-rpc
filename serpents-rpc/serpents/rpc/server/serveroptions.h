#ifndef SERVER_OPTIONS_H_
#define SERVER_OPTIONS_H_

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

//serpents libs
#include "serpents/rpc/base.h"
//xmlrpc-c libs
#include "xmlrpc-c\server_abyss.hpp"
//c++ system libs
#include <string>

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