/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <common/basic_definitions.h>

#include "logger.h"
#include "itkproxy.h"
#include "itkproxy_item.h"
#include "itkproxy_pom.h"
#include "itkconnector.h"

#ifdef __cplusplus
extern "C" {
#endif

static void *(*mem_malloc)(size_t size) = &malloc;

char *itkc_getValueFromArgument(const char *argument)
{
    char *fullArgument;
    char *itkValue;
    char *value;

    fullArgument = (char *)mem_malloc((strlen(argument) + 3) * sizeof(char));
    if (fullArgument == NULL)
    {
        return NULL;
    }

    sprintf(fullArgument, "-%s=", argument);

    itkValue = proxy_ITK_ask_cli_argument(fullArgument);
    if (itkValue == NULL)
    {
        UTIL_log(WARN, "The value of the argument %s hasn't been provided.");
        free(fullArgument);
        return NULL;
    }
    value = (char *)mem_malloc((strlen(itkValue) + 1) * sizeof(char));
    strcpy(value, itkValue);

    free(fullArgument);

    return value;
}

/*
 * itk_Item functionality
 */

/**
 * @ingroup itk_Item
 */
typedef struct itk_Item
{
    tag_t itk_ref;    //!< Internal reference to object in the system
    char *id;         //!< Id of the item
    char *name;       //!< Name of the item
    char *type;       //!< Type of the item
    int numRevisions; //!< Number of revisions the item has
} itk_Item;

const char *itkc_item_getId(const itk_Item *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    return item->id;
}

const char *itkc_item_getName(const itk_Item *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    return item->name;
}

const char *itkc_item_getType(const itk_Item *item)
{
    if (item == NULL)
    {
        return NULL;
    }
    return item->type;
}

int itkc_item_getNumRevisions(const itk_Item *item)
{
    if (item == NULL)
    {
        return -1;
    }
    return item->numRevisions;
}

static void m_itkc_item_loadNumRevisions(itk_Item *item)
{
    tag_t *revisions = NULL_TAG;
    int status;

    status = proxy_ITEM_list_all_revs(item->itk_ref, &item->numRevisions, &revisions);
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "Revisions weren't loaded for item [%s].", item->id);
        return;
    }
    proxy_MEM_free(revisions);
}

itk_Item *itkc_findItem(const char *itemId)
{
    const char *attributeNames[] = {"item_id"};
    const char *attributeValues[] = {itemId};
    int numItems = -1;
    tag_t *items = NULL_TAG;
    int status;
    itk_Item *item;

    if (itemId == NULL || strcmp("", itemId) == 0)
    {
        UTIL_log(WARN, "Incorrect itemId, it can't be null or empty.");
        return NULL;
    }

    status = proxy_ITEM_find_items_by_key_attributes(1, attributeNames, attributeValues, &numItems, &items);
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "Error when finding items by id for id [%s].", itemId);
        return NULL;
    }

    if (numItems <= 0)
    {
        UTIL_log(WARN, "Item with id [%s] not found.", itemId);
        proxy_MEM_free(items);
        return NULL;
    }

    item = (itk_Item *)mem_malloc(sizeof(itk_Item));
    if (item == NULL)
    {
        UTIL_log(WARN, "Not allocated memory for object Item.");
        proxy_MEM_free(items);
        return NULL;
    }
    item->itk_ref = items[0];
    proxy_MEM_free(items);
    item->id = itkproxy_item_allocId();
    strcpy(item->id, itemId);
    item->name = itkproxy_item_allocName();
    item->type = itkproxy_item_allocType();
    item->numRevisions = -1;

    status = proxy_ITEM_ask_name(item->itk_ref, item->name);
    if (status != ITK_ok)
    {
        itkc_freeItem(item);
        return NULL;
    }

    status = proxy_ITEM_ask_type(item->itk_ref, item->type);
    if (status != ITK_ok)
    {
        itkc_freeItem(item);
        return NULL;
    }

    m_itkc_item_loadNumRevisions(item);

    return item;
}

void itkc_freeItem(itk_Item *item)
{
    if (item == NULL)
    {
        return;
    }

    free(item->id);
    free(item->name);
    free(item->type);
    free(item);
}

/**
 * @ingroup itk_User
 * @{
 */
typedef struct itk_User
{
    tag_t itk_ref; //!< Internal reference to object in the system
    char *id;      //!< id of the user
    char *name;    //!< name of the user
} itk_User;

const char *itkc_user_getId(const itk_User *user)
{
    if (user == NULL)
    {
        return NULL;
    }
    return user->id;
}

const char *itkc_user_getName(const itk_User *user)
{
    if (user == NULL)
    {
        return NULL;
    }
    return user->name;
}

itk_User *m_itkc_allocUser(void)
{
    itk_User *user;

    user = (itk_User *)mem_malloc(sizeof(itk_User));
    if (user == NULL)
    {
        UTIL_log(WARN, "Not allocated memory for object User.");
        return NULL;
    }

    user->name = NULL;

    return user;
}

/**
 * @brief
 * @param[in] user
 */
void m_itkc_freeUser(itk_User *user)
{
    if (user == NULL)
    {
        return;
    }

    proxy_MEM_free(user->id);
    proxy_MEM_free(user->name);

    free(user);
}

/**
 * @}
 */

/**
 * @ingroup itk_Group
 * @{
 */
typedef struct itk_Group
{
    tag_t itk_ref; //!< Internal reference to object in the system
    char *name;    //!< name of the group
} itk_Group;

const char *itkc_group_getName(const itk_Group *group)
{
    if (group == NULL)
    {
        return NULL;
    }
    return group->name;
}

/**
 * @brief
 * @return
 */
itk_Group *m_itkc_allocGroup(void)
{
    itk_Group *group;

    group = (itk_Group *)mem_malloc(sizeof(itk_Group));
    if (group == NULL)
    {
        UTIL_log(WARN, "Not allocated memory for object Group.");
        return NULL;
    }
    group->name = NULL;
    return group;
}

/**
 * @brief
 * @param[in] group
 */
void m_itkc_freeGroup(itk_Group *group)
{
    if (group == NULL)
    {
        return;
    }
    proxy_MEM_free(group->name);
    free(group);
}

/**
 * @}
 */

/**
 * @ingroup itk_Owner
 */
typedef struct itk_Owner
{
    itk_User *user;   //!< Owner user
    itk_Group *group; //!< Owner group
} itk_Owner;

itk_Owner *itkc_getOwner(const itk_Item *item)
{
    tag_t t_user;
    tag_t t_group;
    itk_Owner *owner;
    int status;

    status = proxy_POM_ask_owner(item->itk_ref, &t_user, &t_group);
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "(%d) Error when getting ownership from item [%s].", status, item->id);
        return NULL;
    }

    owner = (itk_Owner *)mem_malloc(sizeof(itk_Owner));
    if (owner == NULL)
    {
        UTIL_log(WARN, "Error when allocating memory for object Owner.");
        return NULL;
    }
    owner->user = NULL;
    owner->group = NULL;

    owner->user = m_itkc_allocUser();
    if (owner->user == NULL)
    {
        UTIL_log(WARN, "Error when allocating memory for object User within Owner.");
        itkc_freeOwner(owner);
        return NULL;
    }
    owner->user->itk_ref = t_user;

    status = proxy_POM_ask_user_id(owner->user->itk_ref, &(owner->user->id));
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "(%d) Error when getting the id from owning user.", status);
        itkc_freeOwner(owner);
        return NULL;
    }

    status = proxy_POM_ask_user_name(owner->user->itk_ref, &(owner->user->name));
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "(%d) Error when getting the name from owning user.", status);
        itkc_freeOwner(owner);
        return NULL;
    }

    owner->group = m_itkc_allocGroup();
    if (owner->group == NULL)
    {
        UTIL_log(WARN, "Error when allocating memory for object Group within Owner.");
        itkc_freeOwner(owner);
        return NULL;
    }
    owner->group->itk_ref = t_group;

    status = proxy_POM_ask_group_name(owner->group->itk_ref, &(owner->group->name));
    if (status != ITK_ok)
    {
        UTIL_log(WARN, "(%d) Error when getting the name from owning group.", status);
        itkc_freeOwner(owner);
        return NULL;
    }

    return owner;
}

void itkc_freeOwner(itk_Owner *owner)
{
    if (owner == NULL)
    {
        return;
    }

    m_itkc_freeUser(owner->user);
    m_itkc_freeGroup(owner->group);
    free(owner);
}

itk_User *itkc_getOwningUser(const itk_Owner *owner)
{
    if (owner == NULL)
    {
        return NULL;
    }
    return owner->user;
}

itk_Group *itkc_getOwningGroup(const itk_Owner *owner)
{
    if (owner == NULL)
    {
        return NULL;
    }
    return owner->group;
}

#ifdef __cplusplus
}
#endif
