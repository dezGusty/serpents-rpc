#ifndef SSL_SERVER_LOG_H_
#define SSL_SERVER_LOG_H_
#pragma once
#include "base.h"
#include <sstream>

// log4cpp

#if USE_LOG4CPP ==1
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
			static SSL_Server_Logger& getInstance()
			{
				static SSL_Server_Logger INSTANCE;
				return INSTANCE;
			}
			~SSL_Server_Logger(void);
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
		void SSL_Server_Logger::addAppender(std::string& type, std::string& fileName){
			log4cpp::Appender *appender = new log4cpp::FileAppender(type, fileName);
			log4cpp::PatternLayout * l = new log4cpp::PatternLayout();
			l->setConversionPattern("[%d{%H:%M:%S:%U}] %m%n");
			appender->setLayout(l);
			root.addAppender(appender);

		}
		SSL_Server_Logger::SSL_Server_Logger() : root(log4cpp::Category::getRoot()){

		}
		void SSL_Server_Logger::error(std::string& s){
			root.error("ERROR: " + s);
		}
		void SSL_Server_Logger::info(std::string& s){
			root.info("INFO: " + s);
		}
		void SSL_Server_Logger::warn(std::string& s){
			root.warn("WARN: " + s);
		}
		SSL_Server_Logger::~SSL_Server_Logger(void){

		}


#endif

#if USE_LOG4CPP ==1

		SSL_SERVER_API void LOG_INFO_(const char* argFile,
			int argLineNb,
			const char* argFunction,
			std::stringstream& argString)
		{
			SSL_Server_Logger::getInstance().info(std::string(argFile));
		}
		SSL_SERVER_API	void LOG_WARN_(const char* argFile,
			int argLineNb,
			const char* argFunction,
			std::stringstream& argString)
		{
			std::stringstream ss;
			ss << "In file: " << argFile << std::endl << "\tOn line: " << argLineNb << std::endl
				<< "\tIn function: " << argFunction << std::endl << "\tWarning: " << argString.str();
			SSL_Server_Logger::getInstance().error(ss.str());
		}
		SSL_SERVER_API void LOG_ERROR_(const char* argFile,
			int argLineNb,
			const char* argFunction,
			std::stringstream& argString)
		{
			std::stringstream ss;
			ss << "In file: " << argFile << std::endl << "\tOn line: " << argLineNb << std::endl
				<< "\tIn function: " << argFunction << std::endl << "\tError: " << argString.str();
			SSL_Server_Logger::getInstance().error(ss.str());
		}

		SSL_SERVER_API void SetLogTarget_(std::string type, std::string name){
			serpents::log::SSL_Server_Logger::getInstance().addAppender(type, name);
		}


#else
		void LOG_(std::stringstream& argString){}
		void SetLogTarget(std::string type, std::string name){}
#endif
	}
}
#define LOG_INFO(f) \
do {\
std::stringstream s; \
	s << f; \
	serpents::log::LOG_INFO_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)

#define LOG_WARN(f) \
do {\
std::stringstream s; \
	s << f; \
	serpents::log::LOG_WARN_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)

#define LOG_ERROR(f) \
do {\
std::stringstream s; \
	s << f; \
	serpents::log::LOG_ERROR_(__FILE__, __LINE__, __FUNCTION__, s); \
} while (0)
#define START_LOGGING(type, name)\
		do{\
			std::stringstream stype; \
			std::stringstream sname;\
			stype << type;\
			sname << name;\
			serpents::log::SetLogTarget_(stype.str(), sname.str()); \
		} while (0)

#endif // SSL_SERVER_LOG_H_