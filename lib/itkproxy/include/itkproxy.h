/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ITK_PROXY_H__
#define __ITK_PROXY_H__

#include "defs.h"
#include "types.h"

/**
 * @defgroup itkproxy ITK Proxy
 * @brief Proxy functionality wrapping calls to ITK API.
 *
 * The module wraps every function from Siemens ITK API to be used
 * by the business logic, isolating it from the actual calls to ITK.
 *
 * @note The output arguments to be freed (marked as @c F in
 * the parameter documentation) @b MUST be freed using the function
 * @link proxy_MEM_free @endlink.
 *
 * @section nomenclature Nomenclature
 * As nomenclature convention, every proxy wrapper has @c proxy_ as
 * prefix in front of the name of the wrapped function. The signature
 * of the wrapping function must be, however, exactly the same
 * as the signature of the wrapped function.
 *
 * @section additional_functions Additional functions
 * There are also additional functions that aren't wrapping any ITK function,
 * but are helpers or hide references to ITK, in order to be used along
 * within the business logic.
 *
 * @{
 */

/**
 * @defgroup itkproxy_item ITK Proxy Item
 * @brief Proxy functionality wrapping calls to ITK Item API.
 */

/**
 * @defgroup itkproxy_pom ITK Proxy POM
 * @brief Proxy functionality wrapping calls to ITK POM API.
 */

/**
 * @brief
 * @return
 */
DLLEXPORT int proxy_ITK_auto_login(void);

/**
 * @brief
 * @param[in] unsavedIgnoredStuff
 * @return
 */
DLLEXPORT int proxy_ITK_exit_module(const boolean ignoreUnsavedStuff);

/**
 * @brief Gets the value of command line argument given as argument.
 * @param[in] key Name of the command line argument
 * @return Value of the command line argument
 */
DLLEXPORT char *proxy_ITK_ask_cli_argument(const char *key);

/**
 * @brief Frees memory allocated by Siemens ITK API.
 * @param[in] ptr Pointer of the allocated memory to be freed.
 */
DLLEXPORT void proxy_MEM_free(void *ptr);

/**
 * @brief
 * @param[in] message
 * @param[in] ...
 */
DLLEXPORT void proxy_TC_write_syslog(const char *message, ...);

/**
 * @}
 */

#endif

#ifdef __cplusplus
}
#endif
