/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include <tccore/item.h>
#include "itkproxy_item.h"

char *itkproxy_item_allocId(void)
{
    return malloc((ITEM_id_size_c + 1) * sizeof(char));
}

char *itkproxy_item_allocName(void)
{
    return malloc((ITEM_name_size_c + 1) * sizeof(char));
}

char *itkproxy_item_allocType(void)
{
    return malloc((ITEM_type_size_c + 1) * sizeof(char));
}

int (*f_ITEM_ask_name)(tag_t item, char *name) = &ITEM_ask_name;
int proxy_ITEM_ask_name(tag_t item, char *name)
{
    return f_ITEM_ask_name(item, name);
}

int (*f_ITEM_ask_type)(tag_t item, char *type) = &ITEM_ask_type;
int proxy_ITEM_ask_type(tag_t item, char *type)
{
    return f_ITEM_ask_type(item, type);
}

int (*f_ITEM_list_all_revs)(tag_t item, int *count, tag_t **revisions) = &ITEM_list_all_revs;
int proxy_ITEM_list_all_revs(tag_t item, int *count, tag_t **revisions)
{
    return f_ITEM_list_all_revs(item, count, revisions);
}

int (*f_ITEM_find_items_by_key_attributes)(int numAttributes, const char **attributeNames, const char **attributeValues, int *numItems, tag_t **itemTags) = &ITEM_find_items_by_key_attributes;
int proxy_ITEM_find_items_by_key_attributes(int numAttributes, const char **attributeNames, const char **attributeValues, int *numItems, tag_t **itemTags)
{
    return f_ITEM_find_items_by_key_attributes(numAttributes, attributeNames, attributeValues, numItems, itemTags);
}

#ifdef __cplusplus
}
#endif
