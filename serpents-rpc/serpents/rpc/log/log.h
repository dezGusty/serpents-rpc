
#ifndef LOGGER_H_
#define LOGGER_H_

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

#ifdef USE_LOG4CPP

//serpent libs
#include "serpents/rpc/base.h"
#include "serpents\rpc\log\log_build_opts.h"
//log4cpp libs
#include "log4cpp/Category.hh"

#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

//guslib

#include "guslib\common\singleton.hpp"

namespace serpents{
  class SERPENTSDLL Logger
  {
  public:
	  Logger(void);
    ~Logger(void);
    void addAppender(std::string, std::string);
    void error(std::string);
    void info(std::string);
    void warn(std::string);
  protected:

    log4cpp::Category& root;


    
  };
  typedef guslib::Singleton<Logger> Log;
  SERVERMGR_EXPIMP_TEMPLATE template class SERVERMGR_EXPORT_SYMBOL guslib::Singleton <Logger>;
}

#endif
#endif // LOGGER_H_

