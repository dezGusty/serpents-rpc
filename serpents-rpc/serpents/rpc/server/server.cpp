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

#include "serpents\rpc\server\server.h"

namespace serpents{
  class Server::Impl{
  public:
    std::map<std::string, std::string> logmap;
    ServerOptions* soPtr;

  };
  //implementation to be moved to corresponding libs 
  Server::Server() {
    Impl_ = new Impl();
  }
  void Server::setRepository(serpents::FunctionRepository& fr){
    this->repository = &fr;
  }
  void Server::addLogTarget(std::string type, std::string fileName){
    Impl_->logmap.insert(std::pair<std::string, std::string>(fileName, type));
  }
  std::map<std::string, std::string>* Server::getLogTargets(){
    return &Impl_->logmap;
  }
  FunctionRepository* Server::getRepository(){
    return this->repository;
  }
  void Server::setServerOptionsImpl(ServerOptions* so){
    Impl_->soPtr = so;
  }
  ServerOptions* Server::getServerOptions(){
    if (Impl_->soPtr == nullptr)
      throw std::exception("server options is a null pointer");
    return this->Impl_->soPtr;
  }

}
