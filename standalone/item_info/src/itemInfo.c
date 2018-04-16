/**
 * @file
 * @brief
 * @since 04-Sep-2017
 * @author José Alberto García Sánchez
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "logger.h"
#include "itkconnector.h"

#include "itemInfo.h"

typedef struct ItemInfo
{
	itk_Owner *owner;
	itk_Item *item;
} ItemInfo;

/**
 * @brief wrap function to allocate memory
 */
static void *(*m_memAlloc)(size_t _Size) = &malloc;

/**
 * @brief wrap function to write to standard output
 */
static int (*m_write)(const char *Format, ...) = &printf;

unsigned int m_isItemInfoLoaded(const ItemInfo *itemInfo)
{
	return (itemInfo != NULL && itkc_item_getNumRevisions(itemInfo->item) >= 0);
}

ItemInfo *ITEM_INFO_get(char const *itemId)
{
	ItemInfo *itemInfo;

	itemInfo = m_memAlloc(sizeof(ItemInfo));
	if (itemInfo != NULL)
	{
		itemInfo->item = itkc_findItem(itemId);
		if (itemInfo->item == NULL)
		{
			free(itemInfo);
			return NULL;
		} else {
			itemInfo->owner = itkc_getOwner(itemInfo->item);
		}
	}

	return itemInfo;
}

void ITEM_INFO_write(const ItemInfo *itemInfo)
{
	if (m_isItemInfoLoaded(itemInfo))
	{
		const itk_Item *_item = itemInfo->item;
		const itk_User *_user = itkc_getOwningUser(itemInfo->owner);
		itk_Group *_group = itkc_getOwningGroup(itemInfo->owner);
		m_write("item.id = [%s] ->\n\
\titem.name = [%s]\n\
\titem.type = [%s]\n\
\titem.numRevs = [%d]\n\
\tuser.id = [%s]\n\
\tuser.name = [%s]\n\
\tgroup.name = [%s]\n",
				itkc_item_getId(_item), itkc_item_getName(_item), itkc_item_getType(_item), itkc_item_getNumRevisions(_item),
				itkc_user_getId(_user), itkc_user_getName(_user), itkc_group_getName(_group));
	}
	else if (itemInfo != NULL)
	{
		m_write("Item with id [%s] not found or not yet loaded.\n", itkc_item_getId(itemInfo->item));
	}
}

void ITEM_INFO_free(ItemInfo **itemInfo)
{
	if (*itemInfo == NULL)
	{
		return;
	}

	itkc_freeItem((*itemInfo)->item);
	itkc_freeOwner((*itemInfo)->owner);
	free(*itemInfo);
	*itemInfo = NULL;
}
