/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ITK_PROXY_ITEM_H__
#define __ITK_PROXY_ITEM_H__

#include <unidefs.h>
#include "defs.h"

/**
 * @ingroup itkproxy_item
 * @{
 */

/**
 * @brief Allocates memory to store the item id.
 *
 * The allocated memory must be freed.
 * @return Allocated memory
 */
DLLEXPORT char *itkproxy_item_allocId(void);

/**
 * @brief Allocates memory to store the item name.
 *
 * The allocated memory must be freed.
 * @return Allocated memory
 */
DLLEXPORT char *itkproxy_item_allocName(void);

/**
 * @brief Allocates memory to store the item type.
 *
 * The allocated memory must be freed;
 * @return Allocated memory
 */
DLLEXPORT char *itkproxy_item_allocType(void);

/**
 * @brief
 * @param[in] item
 * @param[out] name
 * @return
 */
DLLEXPORT int proxy_ITEM_ask_name(tag_t item, char *name);

/**
 * @brief
 * @param[in] item
 * @param[out] type
 * @return
 */
DLLEXPORT int proxy_ITEM_ask_type(tag_t item, char *type);

/**
 * @brief
 * @param[in] item
 * @param[out] count
 * @param[out] revisions (F)
 * @return
 */
DLLEXPORT int proxy_ITEM_list_all_revs(tag_t item, int *count, tag_t **revisions);

/**
 * @brief
 * @param[in] numAttributes
 * @param[in] attributeNames
 * @param[in] attributeValues
 * @param[out] numItems
 * @param[out] items (F)
 * @return
 */
DLLEXPORT int proxy_ITEM_find_items_by_key_attributes(int numAttributes, const char **attributeNames, const char **attributeValues, int *numItems, tag_t **items);

/**
 * @}
 */

#endif

#ifdef __cplusplus
}
#endif
