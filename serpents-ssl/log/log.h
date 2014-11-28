#ifndef SSL_LOG_H_
#define SSL_LOG_H_

#include "serpents-ssl\base.h"
#include <sstream>

// log4cpp

#if USE_LOG4CPP ==1
#pragma once
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"


namespace serpents{
  namespace log{
    class SSL_SERVER_API SSL_Server_Logger{
    public:
      static SSL_Server_Logger& getInstance();
      void addAppender(std::string&, std::string&);
      void error(std::string&);
      void info(std::string&);
      void warn(std::string&);
    protected:
      log4cpp::Category& root;
      SSL_Server_Logger(void);
      SSL_Server_Logger(const SSL_Server_Logger& rLogger);
      SSL_Server_Logger operator=(const SSL_Server_Logger& rLogger);
    };

    SSL_SERVER_API void LOG_INFO_(const char* argFile,  int argLineNb,  const char* argFunction,
                std::stringstream& argString);
    SSL_SERVER_API  void LOG_WARN_(const char* argFile,  int argLineNb,  const char* argFunction,
                std::stringstream& argString);
    SSL_SERVER_API void LOG_ERROR_(const char* argFile,  int argLineNb,  const char* argFunction,
                std::stringstream& argString);
    SSL_SERVER_API void SetLogTarget_(std::string type, std::string name);


  }
}
#endif
#define LOG_INFO(f) \
do {\
  std::stringstream s; \
  s << f; \
  serpents::log::LOG_INFO_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)

#define LOG_WARN(f) \
do {  \
  std::stringstream s; \
  s << f; \
  serpents::log::LOG_WARN_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)

#define LOG_ERROR(f) \
do {  \
  std::stringstream s; \
  s << f; \
  serpents::log::LOG_ERROR_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)
#define START_LOGGING(type, name)\
do{  \
  std::stringstream stype; \
  std::stringstream sname; \
  stype << type; \
  sname << name; \
  serpents::log::SetLogTarget_(stype.str(), sname.str()); \
} while (0)

#endif // SSL_LOG_H_
