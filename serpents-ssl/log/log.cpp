#include "serpents-ssl\log\log.h"

namespace serpents{
	namespace log{
		SSL_Server_Logger& SSL_Server_Logger::getInstance()
		{
			static SSL_Server_Logger INSTANCE;
			return INSTANCE;
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
		void SSL_Server_Logger::addAppender(std::string& type, std::string& fileName){
			log4cpp::Appender *appender = new log4cpp::FileAppender(type, fileName);
			log4cpp::PatternLayout * l = new log4cpp::PatternLayout();
			l->setConversionPattern("[%d{%H:%M:%S:%U}] %m%n");
			appender->setLayout(l);
			root.addAppender(appender);

		}

		void LOG_INFO_(const char* argFile,
			int argLineNb,
			const char* argFunction,
			std::stringstream& argString)
		{
			SSL_Server_Logger::getInstance().info(std::string(argFile));
		}
		void LOG_WARN_(const char* argFile,
			int argLineNb,
			const char* argFunction,
			std::stringstream& argString)
		{
			std::stringstream ss;
			ss << "In file: " << argFile << std::endl << "\tOn line: " << argLineNb << std::endl
				<< "\tIn function: " << argFunction << std::endl << "\tWarning: " << argString.str();
			SSL_Server_Logger::getInstance().error(ss.str());
		}
		void LOG_ERROR_(const char* argFile,
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
	}
}

