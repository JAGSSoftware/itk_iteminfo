/**
 * @file
 * @brief
 * @since 28-08-2017
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include "types.h"

/**
 * @ingroup item_info
 * @{
 */

/**
 * @brief Read the arguments from command line.
 * @return @code true @endcode if the arguments have been properly read,
 * @code false @endcode otherwise.
 */
boolean readArguments(void);

/**
 * @brief
 */
void freeArguments(void);

/**
 * @brief
 */
void logArguments(void);

/**
 * @brief
 * @return
 */
const char *getItemId(void);

/**
 * @}
 */
#endif

#ifdef __cplusplus
}
#endif
