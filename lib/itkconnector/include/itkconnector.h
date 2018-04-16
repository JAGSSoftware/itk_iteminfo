/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __ITKCONNECTOR_H__
#define __ITKCONNECTOR_H__

#include "defs.h"

/**
 * @defgroup itkconnector ITK Connector
 * @brief The module is the interface between the ITK API and the rest of the functionality.
 *
 * It isolates the rest of the functionality from Siemens ITK, allowing better
 * dependency management, build, testing, etc. The business logic @b MUST be
 * independent of Siemens ITK functions and structures.
 * @{
 */

/**
 * @defgroup itk_Item itk_Item
 * @brief ITK structure for Item objects.
 */

/**
 * @defgroup itk_User itk_User
 * @brief ITK structure for User objects.
 */

/**
 * @defgroup itk_Group itk_Group
 * @brief ITK structure for Group objects.
 */

/**
 * @defgroup itk_Owner itk_Owner
 * @brief ITK structure for Owner objects.
 */

/**
 * @ingroup itk_Item
 * @{
 */

/**
 * @brief Item object definition
 */
typedef struct itk_Item itk_Item;

/**
 * @brief Get the id from the item given as argument.
 * @param[in] item Item to get the id from
 * @return Id of the item
 */
DLLEXPORT const char *itkc_item_getId(const itk_Item *item);

/**
 * @brief Get the name from the item given as argument.
 * @param[in] item Item to get the name from
 * @return Name of the item
 */
DLLEXPORT const char *itkc_item_getName(const itk_Item *item);

/**
 * @brief Get the type from the item given as argument.
 * @param[in] item Item to get the type from
 * @return Type of the item
 */
DLLEXPORT const char *itkc_item_getType(const itk_Item *item);

/**
 * @brief Get the number of revisions the item given as argument has.
 * @param[in] item Item to get the number of revisions from
 * @return Number of revisions the item has
 */
DLLEXPORT int itkc_item_getNumRevisions(const itk_Item *item);

/**
 * @brief Finds the item with id given as argument.
 * @param[in] itemId Id of the item to be found
 * @return Found item, @code NULL @endcode if nothing was found or by error
 */
DLLEXPORT itk_Item *itkc_findItem(const char *itemId);

/**
 * @brief Frees the memory allocated for the item given as argument.
 * @param[in] item Item to be freed
 */
DLLEXPORT void itkc_freeItem(itk_Item *item);

/**
 * @}
 */

/**
 * @ingroup itk_User
 * @{
 */

/**
 * @brief User object definition
 */
typedef struct itk_User itk_User;

/**
 * @brief Get the id from the user given as argument.
 * @param[in] user User to get the id from
 * @return Id of the user
 */
DLLEXPORT const char *itkc_user_getId(const itk_User *user);

/**
 * @brief Get the name from the user given as argument.
 * @param[in] user User to get the name from
 * @return Name of the user
 */
DLLEXPORT const char *itkc_user_getName(const itk_User *user);

/**
 * @}
 */

/**
 * @ingroup itk_Group
 * @{
 */

/**
 * @brief Group object definition
 */
typedef struct itk_Group itk_Group;

/**
 * @brief Get the name from the group given as argument.
 * @param[in] group Group to get the name from
 * @return Name of the group
 */
DLLEXPORT const char *itkc_group_getName(const itk_Group *group);

/**
 * @}
 */

/**
 * @ingroup itk_Owner
 * @{
 */

/**
 * @brief Owner object definition
 */
typedef struct itk_Owner itk_Owner;

/**
 * @brief Get the owner of the item given as parameter.
 * @param[in] item Item to get the ownership from
 * @return Owner of the item, @c NULL is case of error or not found
 */
DLLEXPORT itk_Owner *itkc_getOwner(const itk_Item *item);

/**
 * @brief Frees the allocated memory for the object.
 * @param[in] owner Object to be freed
 */
DLLEXPORT void itkc_freeOwner(itk_Owner *owner);

/**
 * @brief Get the owning user from the given owner parameter.
 * @param[in] owner
 * @return Owning user
 */
DLLEXPORT itk_User *itkc_getOwningUser(const itk_Owner *owner);

/**
 * @brief Get the owning group from the given owner parameter.
 * @param[in] owner
 * @return Owning group
 */
DLLEXPORT itk_Group *itkc_getOwningGroup(const itk_Owner *owner);

/**
 * @}
 */

/**
 * @brief Get the value of the command line argument name given as argument.
 * @param[in] key Name of the argument from command line to get the value from
 * @return Value of the command line argument
 */
DLLEXPORT char *itkc_getValueFromArgument(const char *key);

/**
 * @}
 */

#endif // __ITKCONNECTOR_H__

#ifdef __cplusplus
}
#endif
