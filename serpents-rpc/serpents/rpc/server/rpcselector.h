
#ifndef RPCSELECTOR_H_
#define RPCSELECTOR_H_

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

#ifdef SERPENTSRPC_EXPORTS
#define RPCSELECTDLL _declspec(dllexport)
#else
#define RPCSELECTDLL _declspec(dllimport)
#endif
//serpents libs
#include "serpents/rpc/server/serverstartup.h"
#ifdef USE_LOG4CPP
#include "serpents/rpc/log/log.h"
#endif

//c++ system libs
#ifdef WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif
#include <stdexcept>
#include <iostream>
#include <string>
#include <cassert>
namespace serpents{
	class ServerStartUp;


	class RPCSELECTDLL RPCSelector
	{
	private:
		ServerStartUp* ServerStartUpImpl_;
		Server* server_;
	public:
		void startServer();
		void selectRPCMethod(Server& server, std::string method);
		void stopServer();
		RPCSelector();
		~RPCSelector();
	};
}

#endif  // RPCSELECTOR_H_


