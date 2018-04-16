/**
 * @file
 * @brief
 * @since 25-Jan-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ITK_PROXY_POM__
#define __ITK_PROXY_POM__

#include <unidefs.h>
#include "defs.h"

/**
 * @ingroup itkproxy_pom
 * @{
 */

/**
 * @brief
 * @return
 */
DLLEXPORT int proxy_POM_init_module(void);

/**
 * @brief
 * @param[in] item
 * @param[out] user
 * @param[out] group
 * @return
 */
DLLEXPORT int proxy_POM_ask_owner(tag_t item, tag_t *user, tag_t *group);

/**
 * @brief
 * @param[in] user
 * @param[out] id (F)
 * @return
 */
DLLEXPORT int proxy_POM_ask_user_id(tag_t user, char **id);

/**
 * @brief
 * @param[in] user
 * @param[out] name (F)
 * @return
 */
DLLEXPORT int proxy_POM_ask_user_name(tag_t user, char **name);

/**
 * @brief
 * @param[in] group
 * @param[out] name (F)
 * @return
 */
DLLEXPORT int proxy_POM_ask_group_name(tag_t group, char **name);

/**
 * @}
 */
#endif

#ifdef __cplusplus
}
#endif