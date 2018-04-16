/**
 * @file
 * @brief
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup logging
 * @{
 */

#define FORMAT_TIME_SIZE 20 //!< Size for formatted time string
#define LOG_LEVEL_SIZE 8	//!< Size for formatted log level string
#define MESSAGE_SIZE 1024   //!<  Size of output message

/**
 * @brief Default logger function, to be used if none is set by the user.
 * @param[in] message Message to be written to the logger
 * @return @c EOF in case of error, non-negative value otherwise
 * @see puts();
 */
int (*loggerFunction)(const char *message) = &puts;

/**
 * @brief Function to get the current time
 * @see @code time(time_*): time_t @endcode
 */
static time_t (*m_getCurrentTime)(time_t *_time) = &time;

/**
 * @brief Keep the log level threshold for logging messages.
 */
static LogLevel minimumLogLevel = ERROR;

/**
 * @brief Keep if @c \\n is appended to the logged message
 */
static unsigned int appendLineCarrier = 0;

/**
 * @brief Format the time to the pattern <em>yyyy-MMM-dd hh:mi:ss</em>
 *
 * The months happen in english short format of three characters lenght.
 *
 * @return formatted string
 */
static char *m_formatTime(const time_t currentTime)
{
	static const char monthName[][4] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static char string[FORMAT_TIME_SIZE + 1] = "\0";

	struct tm *calendar;

	calendar = gmtime(&currentTime);

	sprintf(string, "%d-%3s-%02d %02d:%02d:%02d",
			calendar->tm_year + 1900,
			monthName[calendar->tm_mon],
			calendar->tm_mday,
			calendar->tm_hour,
			calendar->tm_min,
			calendar->tm_sec);

	return string;
}

/**
 * @brief Format the log level to be written along the log message.
 *
 * @param[in] logLevel log level to be written
 * @return formatted string
 */
static char *m_formatLogLevel(const LogLevel logLevel)
{
	static const char logLevelName[][6] = {
		"ERROR", "WARN", "INFO", "DEBUG", "TRACE"};
	static char string[LOG_LEVEL_SIZE + 1] = "\0";

	sprintf(string, "[%-5s]", logLevelName[logLevel]);

	return string;
}

void UTIL_log(const LogLevel logLevel, const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	if (logLevel <= minimumLogLevel)
	{
		char newFormat[MESSAGE_SIZE + 1] = "\0";
		char message[MESSAGE_SIZE + 1] = "\0";

		strcat(newFormat, m_formatLogLevel(logLevel));
		strcat(newFormat, " ");
		strcat(newFormat, m_formatTime(m_getCurrentTime(NULL)));
		strcat(newFormat, ": ");
		strcat(newFormat, fmt);

		if (appendLineCarrier)
		{
			strcat(newFormat, "\n");
		}

		vsprintf(message, newFormat, argp);

		loggerFunction(message);
	}

	va_end(argp);
}

void UTIL_setLogLevel(const LogLevel logLevel)
{
	minimumLogLevel = logLevel;
}

void UTIL_setLoggerFunction(int (*function)(const char *))
{
	if (function != NULL)
	{
		loggerFunction = function;
	}
}

void UTIL_setAppendLineCarrier(unsigned int value)
{
	appendLineCarrier = (value != 0);
}

	/**
 * @}
 */

#ifdef __cplusplus
}
#endif
