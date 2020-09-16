#ifndef _LOG_H_
#define _LOG_H_

#include <string>

namespace Log
{
	enum class LogLevel { None = 0, Print, Error, Warn, Info, Debug };

	void setLogLevel(LogLevel level);
	void debug(const std::string& msg);
	void info(const std::string& msg);
	void warn(const std::string& msg);
	void error(const std::string& msg);
	void print(const std::string& msg);
}

#endif // _LOG_H_
