#ifdef USE_LOG4CPP

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

#include "serpents/rpc/log/log.h"
#include "serpents/rpc/server/server.h"
namespace serpents{
  void Logger::addAppender(std::string type, std::string fileName){
    log4cpp::Appender *appender = new log4cpp::FileAppender(type,fileName);
    log4cpp::PatternLayout * l = new log4cpp::PatternLayout();
    l->setConversionPattern("[%d{%H:%M:%S:%U}] %m%n");
    appender->setLayout(l);
    root.addAppender(appender);
    
  }
  Logger::Logger() : root(log4cpp::Category::getRoot()){
     
  }
  void Logger::error(std::string s){
    root.error("ERROR: "+s);
  }
  void Logger::info(std::string s){
    root.info("INFO: "+s);
  }
  void Logger::warn(std::string s){
    root.warn("WARN: "+ s);
  }
  Logger::~Logger(void){
  
  }
  
}

#endif