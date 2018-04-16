/**
 * @file
 * @brief
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "defs.h"
#include "types.h"

/**
 * @addtogroup util
 * @{
 */

/**
 * @brief Check if the environment variable specified by argument has been set.
 * @param[in] variableName Name of the environment variable to be checked
 * @return \c true if the variable is set, \c false otherwise
 */
DLLEXPORT boolean ENV_isSetEnvironmentVariable(const char *variableName);

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif
