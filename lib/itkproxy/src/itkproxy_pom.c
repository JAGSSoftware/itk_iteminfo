/**
 * @file
 * @brief
 * @since 25-Jan-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <pom/pom/pom.h>

#include "itkproxy_pom.h"

int (*f_POM_init_module)(void) = &POM_init_module;
int proxy_POM_init_module(void)
{
    return f_POM_init_module();
}

int (*f_POM_ask_owner)(tag_t item, tag_t *user, tag_t *group) = &POM_ask_owner;
int proxy_POM_ask_owner(tag_t item, tag_t *user, tag_t *group)
{
    return f_POM_ask_owner(item, user, group);
}

int (*f_POM_ask_user_id)(tag_t user, char **id) = &POM_ask_user_id;
int proxy_POM_ask_user_id(tag_t user, char **id)
{
    return f_POM_ask_user_id(user, id);
}

int (*f_POM_ask_user_name)(tag_t user, char **name) = &POM_ask_user_name;
int proxy_POM_ask_user_name(tag_t user, char **name)
{
    return f_POM_ask_user_name(user, name);
}

int (*f_POM_ask_group_name)(tag_t group, char **name) = &POM_ask_group_name;
int proxy_POM_ask_group_name(tag_t group, char **name)
{
    return f_POM_ask_group_name(group, name);
}

#ifdef __cplusplus
}
#endif