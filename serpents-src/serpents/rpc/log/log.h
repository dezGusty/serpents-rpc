#ifndef LOGGER_H_
#define LOGGER_H_

#ifdef USE_LOG4CPP

//serpent libs
#include "serpents/rpc/base.h"

//log4cpp libs
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

#ifdef SERPENTSRPC_EXPORTS
#define LOG_DLL _declspec(dllexport)
#else
#define LOG_DLL _dlecpsec(dllimport)
#endif
namespace serpents{
  class LOG_DLL Logger
  {
  public:
    static Logger& getInstance()
    {
      static Logger INSTANCE;
      return INSTANCE;
    }
    ~Logger(void);
    void addAppender(std::string, std::string);
    void error(std::string);
    void info(std::string);
    void warn(std::string);
  protected:

    log4cpp::Category& root;
    Logger(void);
    Logger(const Logger& rLogger);
    Logger operator=(const Logger& rLogger);
    
  };
  
}

#endif
#endif // LOGGER_H_