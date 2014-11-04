#ifndef REPOSITORY_H
#define REPOSITORY_H

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
#include "serpents/rpc/parameters/parametercontainer.hpp"
#include "serpents/rpc/parameters/retValue.h"
#include "serpents\rpc\base.h"
//c++ system libs
#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "serpents\rpc\server\method.hpp"
namespace serpents{
 
  class SERPENTSDLL FunctionRepository{
  private:
    class  Impl;
    Impl* Impl_;
  public:
    FunctionRepository();
    typedef std::map<std::string, Method *> methodMap;
    void addMethod(Method* method);
   // void executeAll();
    FunctionRepository& operator=(FunctionRepository& fr);
    FunctionRepository(FunctionRepository& fr);
    Impl* getImpl();
    ~FunctionRepository();
    
  };
  class FunctionRepository::Impl{
  public:
	  friend FunctionRepository;
	  methodMap methodContainer;
  };
}


#endif