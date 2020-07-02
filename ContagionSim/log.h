#ifndef _LOG_H_
#define _LOG_H_

#include <string>

// TODO make class or namespace?

enum class LogLevel { Error = 0, Warn, Info, Debug } ;

void setLogLevel(LogLevel level);
void debug (const std::string& msg);
void info  (const std::string& msg);
void warn  (const std::string& msg);
void error (const std::string& msg);

#endif // _LOG_H_