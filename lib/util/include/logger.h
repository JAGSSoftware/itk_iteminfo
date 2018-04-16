/**
 * @file
 * @brief
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "defs.h"

/**
 * @defgroup utililty Utililty functions
 * @brief Utility functions.
 * @{
 */

/**
 * @defgroup logging Logging
 * @brief Logging functionality.
 */

/**
 * @brief Enumeration of error levels for logging.
 * @ingroup logging
 */
typedef enum {
  ERROR, //!< when something is not recoverable
  WARN,  //!< when something is recoverable but should finish the execution
  INFO,  //!< provide log of interest
  DEBUG, //!< for debugging purposes
  TRACE  //!< for fine grained logging
} LogLevel;

/**
 * @brief Writes the current data and time, and the message provided as argument.
 *
 * @param[in] logLevel level of logging
 * @param[in] fmt Message to be written. It can contain formatted data
 * @param[in] ... Data to be printed in the formatted message
 * @ingroup logging
 */
DLLEXPORT void UTIL_log(const LogLevel logLevel, const char *fmt, ...);

/**
  * @brief Set the lowest log level to be written
  *
  * @param[in] logLevel Minimum log level to write
  * @ingroup logging
  */
DLLEXPORT void UTIL_setLogLevel(const LogLevel logLevel);

/**
  * @brief Set the logger function to be used to log the messages.
  *
  * The user must implement a function with signature:
  * @code
  * int loggingFunction(const char* message)
  * @endcode
  *
  * @param[in] function Pointer to the logging function
  * @ingroup logging
  */
DLLEXPORT void UTIL_setLoggerFunction(int (*function)(const char *));

/**
  * @brief Set if the messages to be written will have the line carrier character @c \\n
  * appended.
  *
  * @param[in] value @c 0 to not append the line carrier, otherwise to append the line carrier
  * @ingroup logging
  */
DLLEXPORT void UTIL_setAppendLineCarrier(unsigned int value);

/**
 * @}
 */

#endif

#ifdef __cplusplus
}
#endif
