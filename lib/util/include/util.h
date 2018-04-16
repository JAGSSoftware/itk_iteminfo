/**
 * @file
 * @brief
 * @since 25-08-2017
 * @author José Alberto García Sánchez
 */

#ifndef __UTIL_H__
#define __UTIL_H__

/**
 * @addtogroup util
 * @{
 */

/**
 * @brief Returns the length of the array
 *
 * @param[in] x array whose length is calculated
 * @return number of elements in the array
 */
#define array_length(x) (sizeof(x) / sizeof((x)[0]))

/**
 * @}
 */
#endif
