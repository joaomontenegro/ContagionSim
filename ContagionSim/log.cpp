#include "log.h"

#include <iostream>

namespace Log
{

	LogLevel _logLevel = LogLevel::Info;

	void
		setLogLevel(LogLevel level)
	{
		_logLevel = level;
	}

	void debug(const std::string& msg)
	{
		if (_logLevel >= LogLevel::Debug) {
			std::cout << " * DEBUG: " << msg << std::endl;
		}
	}

	void info(const std::string& msg)
	{
		if (_logLevel >= LogLevel::Info) {
			std::cout << " * INFO: " << msg << std::endl;
		}
	}

	void warn(const std::string& msg)
	{
		if (_logLevel >= LogLevel::Warn) {
			std::cerr << " * WARN: " << msg << std::endl;
		}
	}

	void error(const std::string& msg)
	{
		if (_logLevel >= LogLevel::Error) {
			std::cerr << " * ERROR: " << msg << std::endl;
		}
	}

	void print(const std::string& msg)
	{
		if (_logLevel >= LogLevel::Print) {
			std::cout << msg << std::endl;
		}
	}

}
