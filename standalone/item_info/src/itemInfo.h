/**
 * @file
 * @brief
 * @since 28-08-2017
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ITEM_INFO_H__
#define __ITEM_INFO_H__

/**
 * @ingroup item_info
 * @{
 */

/**
 * @brief Structure with the extracted information from the item
 */
typedef struct ItemInfo ItemInfo;

/**
 * @brief Get the information from the item specified by \c itemId
 * Later the object must be freed using ITEM_INFO_free().
 *
 * @param[in] itemId Id of the item to retrieve
 * @return information of the item
 */
ItemInfo *ITEM_INFO_get(char const *itemId);

/**
 * @brief
 * @param[in] itemInfo
 */
void ITEM_INFO_write(const ItemInfo *itemInfo);

/**
 * @brief
 * @param[in] itemInfo
 */
void ITEM_INFO_free(ItemInfo **itemInfo);

/**
 * @}
 */

#endif

#ifdef __cplusplus
}
#endif
