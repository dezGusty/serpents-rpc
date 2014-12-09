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
//xmlrpc-c libs
//c++ system libs
#include <string>

#ifdef SERPENTSDLL
#define SERVEROPT_DLL _declspec(dllexport)
#else
#define SERVEROPT_DLL _declspec(dllimport)
#endif
namespace serpents{
  class ServerOptions{
  public:
    virtual void portNumber(unsigned int   const& arg) =0;
    //sets the log file for serpents' logger if USELOG4CPP is define
    //does not set te log file for the underlying libs' logger
    virtual void logFileName(std::string    const& arg) = 0;
    virtual void keepaliveTimeout(unsigned int   const& arg) = 0;
    virtual void keepaliveMaxConn(unsigned int   const& arg) = 0;
    virtual void timeout(unsigned int   const& arg) = 0;
    virtual void dontAdvertise(bool           const& arg) = 0;
    virtual void uriPath(std::string    const& arg) = 0;
    virtual void chunkResponse(bool           const& arg) = 0;
    virtual void allowOrigin(std::string    const& arg) = 0;
    virtual void accessCtlMaxAge(unsigned int const& arg) = 0;
    virtual void serverOwnsSignals(bool           const& arg) = 0;
    virtual void expectSigchld(bool           const& arg) = 0;
  };
  
  /*
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
  */
}
#endif  // SERVER_OPTIONS_H_