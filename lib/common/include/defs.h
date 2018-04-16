/**
 * @file
 * @brief General common definitions
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef __DEFS_H__
#define __DEFS_H__

/**
 * @defgroup defs Definitions
 * @brief General common definitions
 * @{
 */

#ifdef _WIN64
#define DLLEXPORT __declspec(dllexport) //<! Definition to export a function
#else
#define DLLEXPORT
#endif

/**
 * @}
 */

#endif

#ifdef __cplusplus
}
#endif // __cplusplus
