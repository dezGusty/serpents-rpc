#ifdef USE_LOG4CPP
#include "log.h"
#include "server.h"
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
		root.error(s);
	}
	void Logger::info(std::string s){
		root.info( s);
	}
	void Logger::warn(std::string s){
		root.warn( s);
	}
	Logger::~Logger(void){
	
	}
	
}

#endif