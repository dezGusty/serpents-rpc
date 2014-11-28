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

#ifndef XMLRPC_C_RETVALUE
#define XMLRPC_C_RETVALUE

//  project libs 
#include "serpents\rpc\parameters\retValue.h"
#include "xmlrpc-c\base.hpp"

namespace serpents
{
  class XMLRPC_CRetValue : public RetValue
  {
    public:
    void setValue(int n) override;
    void setValue(double n) override;
    void setValue(float f) override;
    void setValue(bool b) override;
    void setValue(std::string s) override;
    xmlrpc_c::value* getValue();
    XMLRPC_CRetValue();
    XMLRPC_CRetValue(const XMLRPC_CRetValue& retval) = delete;
    ~XMLRPC_CRetValue();
   
    private:
    class Impl;
    Impl* Impl_;
  };
  
}

#endif // XMLRPC_C_RETVALUE

