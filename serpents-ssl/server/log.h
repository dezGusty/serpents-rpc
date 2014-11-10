#include <sstream>
#include <iostream>

#ifndef USE_LOG4CPP
void log(
	const char* argFile,
	int argLineNb,
	const char* argFunction,
	std::stringstream& argString) {
	std::cout << argFile << ":" << argLineNb << " " << argFunction
		<< " " << argString.str() << std::endl;
}
#else
void log(
	const char* argFile,
	int argLineNb,
	const char* argFunction,
	std::stringstream& argString) {
	std::cout << argFile << ":" << argLineNb << " " << argFunction
		<< " " << argString.str() << " to be changed to logger"<< std::endl;
}
#endif

#define LOG_TEST(f)								\
do {											\
	std::stringstream s;						\
	s << f;										\
	log(__FILE__, __LINE__, __FUNCTION__, s);	\
} while (0)


namespace serpents {
	namespace log{

		class SSLServerLogger{
		public:
			static void print();
		private:
		};
	}
}