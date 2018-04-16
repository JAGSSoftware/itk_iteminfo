/**
 * @file
 * @brief
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// Here is included the source file under test
#include "itkconnector.c"

/**
 * @brief Mock function
 */
static void *mock_malloc(size_t size)
{
    check_expected(size);
    function_called();

    return mock_ptr_type(void *);
}

/**
 * @brief Mock function
 */
char *proxy_ITK_ask_cli_argument(const char *key)
{
    check_expected(key);

    return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
void UTIL_log(const LogLevel logLevel, const char *fmt, ...)
{
    function_called();
    check_expected(logLevel);
    check_expected(fmt);
}

/**
 * @brief Mock function
 */
int proxy_ITEM_find_items_by_key_attributes(int numAttributes, const char **attributeNames, const char **attributeValues, int *numItems, tag_t **items)
{
    int i;
    check_expected(numAttributes);
    check_expected(*attributeNames);
    check_expected(*attributeValues);
    check_expected(*numItems);
    check_expected(*items);

    *numItems = mock_type(int);
    if (*numItems > 0)
    {
        *items = (tag_t *)malloc(sizeof(tag_t) * (*numItems));
        for (i = 0; i < *numItems; i++)
        {
            (*items)[i] = mock_type(tag_t);
        }
    }

    return mock_type(int);
}

/**
 * @brief Mock function
 */
char *itkproxy_item_allocId(void)
{
    return (char *)malloc(32 * sizeof(char));
}

/**
 * @brief Mock function
 */
char *itkproxy_item_allocName(void)
{
    return (char *)malloc(256 * sizeof(char));
}

/**
 * @brief Mock function
 */
char *itkproxy_item_allocType(void)
{
    return (char *)malloc(32 * sizeof(char));
}

/**
 * @brief Mock function
 */
void proxy_MEM_free(void *ptr)
{
    (void)ptr;
    function_called();

    if (ptr != NULL)
    {
        free(ptr);
    }
}

/**
 * @brief Mock function
 */
int proxy_POM_ask_owner(tag_t item, tag_t *user, tag_t *group)
{
    check_expected(item);

    *user = mock_type(tag_t);
    *group = mock_type(tag_t);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_POM_ask_user_id(tag_t user, char **id)
{
    check_expected(user);

    *id = mock_ptr_type(char *);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_POM_ask_user_name(tag_t user, char **name)
{
    check_expected(user);

    *name = mock_ptr_type(char *);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_POM_ask_group_name(tag_t group, char **name)
{
    check_expected(group);

    *name = mock_ptr_type(char *);

    return mock_type(int);
}

/*
 * Unit tests
 */
int proxy_ITEM_list_all_revs(tag_t item, int *numRevisions, tag_t **revisions)
{
    int i;
    check_expected(item);
    check_expected(*numRevisions);
    check_expected(*revisions);

    *numRevisions = mock_type(int);
    if (*numRevisions > 0)
    {
        *revisions = (tag_t *)mem_malloc(sizeof(tag_t) * (*numRevisions));
        for (i = 0; i < *numRevisions; i++)
        {
            (*revisions)[i] = mock_type(tag_t);
        }
    }

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_ITEM_ask_name(tag_t item, char *name)
{
    check_expected(item);
    check_expected(name);

    strcpy(name, mock_ptr_type(char *));

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_ITEM_ask_type(tag_t item, char *type)
{
    check_expected(item);
    check_expected(type);

    strcpy(type, mock_ptr_type(char *));

    return mock_type(int);
}

/*
 * Unit tests
 */
static void test_itkc_item_getId_itemIsNull(void **state)
{
    (void)state;

    assert_ptr_equal(NULL, itkc_item_getId(NULL));
}

static void test_itkc_item_getId_itemIsNotNull(void **state)
{
    itk_Item item;
    (void)state;

    item.id = (char *)malloc(32 * sizeof(char));
    strcpy(item.id, "000123");

    assert_string_equal("000123", itkc_item_getId(&item));

    free(item.id);
}

static void test_itkc_item_getName_itemIsNull(void **state)
{
    (void)state;

    assert_ptr_equal(NULL, itkc_item_getName(NULL));
}

static void test_itkc_item_getName_itemIsNotNull(void **state)
{
    itk_Item item;
    (void)state;

    item.name = (char *)malloc(256 * sizeof(char));
    strcpy(item.name, "item name");

    assert_string_equal("item name", itkc_item_getName(&item));

    free(item.name);
}

static void test_itkc_item_getType_itemIsNull(void **state)
{
    (void)state;

    assert_ptr_equal(NULL, itkc_item_getType(NULL));
}

static void test_itkc_item_getType_itemIsNotNull(void **state)
{
    itk_Item item;
    (void)state;

    item.type = (char *)malloc(256 * sizeof(char));
    strcpy(item.type, "item type v2.0");

    assert_string_equal("item type v2.0", itkc_item_getType(&item));

    free(item.type);
}

static void test_itkc_item_getNumRevisions_itemIsNull(void **state)
{
    (void)state;

    assert_int_equal(-1, itkc_item_getNumRevisions(NULL));
}

static void test_itkc_item_getNumRevisions_itemIsNotNull(void **state)
{
    itk_Item item;
    (void)state;

    item.numRevisions = 2;

    assert_int_equal(2, itkc_item_getNumRevisions(&item));
}

static void test_itkc_user_getId_userIsNull(void **state)
{
    (void)state;

    assert_null(itkc_user_getId(NULL));
}

static void test_itkc_user_getId_userIsNotNull(void **state)
{
    itk_User user;
    (void)state;

    user.id = (char *)malloc(32 * sizeof(char));
    strcpy(user.id, "user01");

    assert_string_equal("user01", itkc_user_getId(&user));

    free(user.id);
}

static void test_itkc_user_getName_userIsNull(void **state)
{
    (void)state;

    assert_null(itkc_user_getName(NULL));
}

static void test_itkc_user_getName_userIsNotNull(void **state)
{
    itk_User user;
    (void)state;

    user.name = (char *)malloc(256 * sizeof(char));
    strcpy(user.name, "Max Mustermann");

    assert_string_equal("Max Mustermann", itkc_user_getName(&user));

    free(user.name);
}

static void test_itkc_group_getName_groupIsNull(void **state)
{
    (void)state;

    assert_null(itkc_group_getName(NULL));
}

static void test_itkc_group_getName_groupIsNotNull(void **state)
{
    itk_Group group;
    (void)state;

    group.name = (char *)malloc(256 * sizeof(char));
    strcpy(group.name, "Group Name");

    assert_string_equal("Group Name", itkc_group_getName(&group));

    free(group.name);
}

static void test_itkc_getValueFromArgument(void **state)
{
    char *_value;
    (void)state;

    expect_string(proxy_ITK_ask_cli_argument, key, "-itemId=");
    will_return(proxy_ITK_ask_cli_argument, "010203");

    _value = itkc_getValueFromArgument("itemId");

    assert_string_equal("010203", _value);

    free(_value);
}

static void test_itkc_getValueFromArgument_nullAllocation(void **state)
{
    char *_value;
    (void)state;

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, 9 * sizeof(char));
    will_return(mock_malloc, NULL);

    _value = itkc_getValueFromArgument("itemId");

    assert_null(_value);
}

static void test_itkc_getValueFromArgument_nullValueForArgument(void **state)
{
    char *_value;
    (void)state;

    expect_string(proxy_ITK_ask_cli_argument, key, "-itemId=");
    will_return(proxy_ITK_ask_cli_argument, NULL);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "The value of the argument %s hasn't been provided.");

    _value = itkc_getValueFromArgument("itemId");

    assert_null(_value);
}

static int mem_malloc_setUp(void **state)
{
    (void)state;
    mem_malloc = &mock_malloc;

    return 0;
}

static int mem_malloc_tearDown(void **state)
{
    (void)state;
    mem_malloc = &malloc;

    return 0;
}

static void test_m_itkc_item_loadNumRevisions(void **state)
{
    itk_Item _item;
    (void)state;

    _item.itk_ref = 101010;
    _item.numRevisions = -1;

    expect_value(proxy_ITEM_list_all_revs, item, 101010);
    expect_value(proxy_ITEM_list_all_revs, *numRevisions, -1);
    expect_value(proxy_ITEM_list_all_revs, *revisions, NULL_TAG);
    will_return(proxy_ITEM_list_all_revs, 2);
    will_return(proxy_ITEM_list_all_revs, 101011);
    will_return(proxy_ITEM_list_all_revs, 101012);
    will_return(proxy_ITEM_list_all_revs, ITK_ok);

    expect_function_call(proxy_MEM_free);

    m_itkc_item_loadNumRevisions(&_item);

    assert_int_equal(2, _item.numRevisions);
}

static void test_m_itkc_item_loadNumRevisions_notOk(void **state)
{
    int _notOk = 1;
    itk_Item _item;
    (void)state;

    _item.id = "000123";
    _item.itk_ref = 101010;
    _item.numRevisions = -1;

    expect_value(proxy_ITEM_list_all_revs, item, 101010);
    expect_value(proxy_ITEM_list_all_revs, *numRevisions, -1);
    expect_value(proxy_ITEM_list_all_revs, *revisions, NULL_TAG);
    will_return(proxy_ITEM_list_all_revs, -1);
    will_return(proxy_ITEM_list_all_revs, _notOk);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Revisions weren't loaded for item [%s].");

    m_itkc_item_loadNumRevisions(&_item);

    assert_int_equal(-1, _item.numRevisions);
}

static void test_itkc_findItem_itemIdIsNull(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Incorrect itemId, it can't be null or empty.");

    _item = itkc_findItem(NULL);

    assert_null(_item);
}

static void test_itkc_findItem_itemIdIsEmpty(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Incorrect itemId, it can't be null or empty.");

    _item = itkc_findItem("");

    assert_null(_item);
}

static void test_itkc_findItem_notOk(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, -1);
    will_return(proxy_ITEM_find_items_by_key_attributes, 1);

    expect_function_call(UTIL_log);

    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Error when finding items by id for id [%s].");

    _item = itkc_findItem("000123");

    assert_null(_item);
}

static void test_itkc_findItem_itemNotFound(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, 0);
    will_return(proxy_ITEM_find_items_by_key_attributes, ITK_ok);

    expect_function_call(UTIL_log);

    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Item with id [%s] not found.");

    expect_function_call(proxy_MEM_free);

    _item = itkc_findItem("000123");

    assert_null(_item);
}

static void test_itkc_findItem_notAllocatedMemory(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(mock_malloc, size, sizeof(itk_Item));
    expect_function_call(mock_malloc);
    will_return(mock_malloc, NULL);

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, 1);
    will_return(proxy_ITEM_find_items_by_key_attributes, (tag_t)101010);
    will_return(proxy_ITEM_find_items_by_key_attributes, ITK_ok);

    expect_function_call(UTIL_log);

    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Not allocated memory for object Item.");

    expect_function_call(proxy_MEM_free);

    _item = itkc_findItem("000123");

    assert_null(_item);
}

static void test_itkc_findItem_nameNotOk(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, 1);
    will_return(proxy_ITEM_find_items_by_key_attributes, (tag_t)101010);
    will_return(proxy_ITEM_find_items_by_key_attributes, ITK_ok);

    expect_value(proxy_ITEM_ask_name, item, 101010);
    expect_not_value(proxy_ITEM_ask_name, name, NULL);
    will_return(proxy_ITEM_ask_name, "");
    will_return(proxy_ITEM_ask_name, 1);

    expect_function_call(proxy_MEM_free);

    _item = itkc_findItem("000123");

    assert_null(_item);
}

static void test_itkc_findItem_typeNotOk(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, 1);
    will_return(proxy_ITEM_find_items_by_key_attributes, (tag_t)101010);
    will_return(proxy_ITEM_find_items_by_key_attributes, ITK_ok);

    expect_value(proxy_ITEM_ask_name, item, 101010);
    expect_not_value(proxy_ITEM_ask_name, name, NULL);
    will_return(proxy_ITEM_ask_name, "item name");
    will_return(proxy_ITEM_ask_name, ITK_ok);

    expect_value(proxy_ITEM_ask_type, item, 101010);
    expect_not_value(proxy_ITEM_ask_type, type, NULL);
    will_return(proxy_ITEM_ask_type, "");
    will_return(proxy_ITEM_ask_type, 1);

    expect_function_call(proxy_MEM_free);

    _item = itkc_findItem("000123");

    assert_null(_item);
}

static void test_itkc_findItem(void **state)
{
    itk_Item *_item;
    (void)state;

    expect_value(proxy_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeNames, "item_id");
    expect_string(proxy_ITEM_find_items_by_key_attributes, *attributeValues, "000123");
    expect_value(proxy_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(proxy_ITEM_find_items_by_key_attributes, *items, NULL_TAG);
    will_return(proxy_ITEM_find_items_by_key_attributes, 1);
    will_return(proxy_ITEM_find_items_by_key_attributes, (tag_t)101010);
    will_return(proxy_ITEM_find_items_by_key_attributes, ITK_ok);

    expect_value(proxy_ITEM_ask_name, item, 101010);
    expect_not_value(proxy_ITEM_ask_name, name, NULL);
    will_return(proxy_ITEM_ask_name, "item name");
    will_return(proxy_ITEM_ask_name, ITK_ok);

    expect_value(proxy_ITEM_ask_type, item, 101010);
    expect_not_value(proxy_ITEM_ask_type, type, NULL);
    will_return(proxy_ITEM_ask_type, "item type v2.0");
    will_return(proxy_ITEM_ask_type, ITK_ok);

    expect_value(proxy_ITEM_list_all_revs, item, 101010);
    expect_value(proxy_ITEM_list_all_revs, *numRevisions, -1);
    expect_value(proxy_ITEM_list_all_revs, *revisions, NULL_TAG);
    will_return(proxy_ITEM_list_all_revs, 2);
    will_return(proxy_ITEM_list_all_revs, 101011);
    will_return(proxy_ITEM_list_all_revs, 101012);
    will_return(proxy_ITEM_list_all_revs, ITK_ok);

    expect_function_call(proxy_MEM_free);
    expect_function_call(proxy_MEM_free);

    _item = itkc_findItem("000123");

    assert_non_null(_item);
    assert_int_equal(101010, _item->itk_ref);
    assert_string_equal("000123", _item->id);
    assert_string_equal("item name", _item->name);
    assert_string_equal("item type v2.0", _item->type);
    assert_int_equal(2, _item->numRevisions);

    itkc_freeItem(_item);
}

static void test_itkc_freeItem_nullItem(void **state)
{
    (void)state;

    itkc_freeItem(NULL);
}

static void test_itkc_freeItem(void **state)
{
    itk_Item *_item;
    (void)state;

    _item = (itk_Item *)malloc(sizeof(itk_Item));
    _item->id = (char *)malloc(16 * sizeof(char));
    _item->name = (char *)malloc(16 * sizeof(char));
    _item->type = (char *)malloc(16 * sizeof(char));

    itkc_freeItem(_item);
}

static void test_m_itkc_allocUser(void **state)
{
    itk_User *_user;
    (void)state;

    _user = m_itkc_allocUser();

    assert_non_null(_user);

    free(_user);
}

static void test_m_itkc_allocUser_nullAllocation(void **state)
{
    itk_User *_user;
    (void)state;

    expect_value(mock_malloc, size, sizeof(itk_User));
    expect_function_call(mock_malloc);
    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Not allocated memory for object User.");

    will_return(mock_malloc, NULL);

    _user = m_itkc_allocUser();

    assert_null(_user);
}

static void test_m_itkc_freeUser(void **state)
{
    itk_User *_user;
    (void)state;

    expect_function_calls(proxy_MEM_free, 2);

    _user = (itk_User *)mem_malloc(sizeof(itk_User));
    _user->id = NULL;
    _user->name = NULL;

    m_itkc_freeUser(_user);
}

static void test_m_itkc_freeUser_nullObject(void **state)
{
    (void)state;

    ignore_function_calls(proxy_MEM_free);

    m_itkc_freeUser(NULL);
}

static void test_m_itkc_allocGroup(void **state)
{
    itk_Group *_group;
    (void)state;

    _group = m_itkc_allocGroup();

    assert_non_null(_group);

    free(_group);
}

static void test_m_itkc_allocGroup_nullAllocation(void **state)
{
    itk_Group *_group;
    (void)state;

    expect_value(mock_malloc, size, sizeof(itk_Group));
    expect_function_call(mock_malloc);
    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Not allocated memory for object Group.");

    will_return(mock_malloc, NULL);

    _group = m_itkc_allocGroup();

    assert_null(_group);
}

static void test_m_itkc_freeGroup(void **state)
{
    itk_Group *_group;
    (void)state;

    expect_function_call(proxy_MEM_free);

    _group = (itk_Group *)mem_malloc(sizeof(itk_Group));
    _group->name = NULL;

    m_itkc_freeGroup(_group);
}

static void test_m_itkc_freeGroup_nullObject(void **state)
{
    (void)state;

    ignore_function_calls(proxy_MEM_free);

    m_itkc_freeGroup(NULL);
}

static void test_itkc_freeOwner(void **state)
{
    itk_Owner *owner;
    (void)state;

    owner = (itk_Owner *)mem_malloc(sizeof(itk_Owner));
    assert_non_null(owner);
    owner->user = NULL;
    owner->group = NULL;

    itkc_freeOwner(owner);
}

static void test_itkc_freeOwner_nullObject(void **state)
{
    (void)state;

    itkc_freeOwner(NULL);
}

static void test_itkc_getOwningUser_nullObject(void **state)
{
    (void)state;
    assert_null(itkc_getOwningUser(NULL));
}

static void test_itkc_getOwningUser(void **state)
{
    itk_User *_user;
    itk_Owner *_owner = (itk_Owner *)(*state);

    _user = itkc_getOwningUser(_owner);

    assert_non_null(_user);
    assert_int_equal(123454321, _user->itk_ref);
    assert_string_equal("0123456789", _user->id);
    assert_string_equal("Max Mustermann", _user->name);
}

static int test_itkc_getOwningUser_setUp(void **state)
{
    itk_Owner *owner;

    owner = (itk_Owner *)mem_malloc(sizeof(itk_Owner));
    owner->user = (itk_User *)mem_malloc(sizeof(itk_User));
    owner->user->itk_ref = 123454321;
    owner->user->id = (char *)mem_malloc(16 * sizeof(char));
    strcpy(owner->user->id, "0123456789");
    owner->user->name = (char *)mem_malloc(32 * sizeof(char));
    strcpy(owner->user->name, "Max Mustermann");
    owner->group = NULL;

    *state = owner;

    return 0;
}

static int test_itkc_getOwningUser_tearDown(void **state)
{
    itk_Owner *_owner = (itk_Owner *)(*state);
    free(_owner->user->id);
    free(_owner->user->name);
    free(_owner->user);
    free(_owner);

    return 0;
}

static void test_itkc_getOwningGroup_nullObject(void **state)
{
    (void)state;
    assert_null(itkc_getOwningGroup(NULL));
}

static void test_itkc_getOwningGroup(void **state)
{
    itk_Group *_group;
    itk_Owner *_owner = (itk_Owner *)(*state);

    _group = itkc_getOwningGroup(_owner);

    assert_non_null(_group);
    assert_int_equal(123454321, _group->itk_ref);
    assert_string_equal("Engineering", _group->name);
}

static int test_itkc_getOwningGroup_setUp(void **state)
{
    itk_Owner *owner;

    owner = (itk_Owner *)mem_malloc(sizeof(itk_Owner));
    owner->group = (itk_Group *)mem_malloc(sizeof(itk_Group));
    owner->group->itk_ref = 123454321;
    owner->group->name = (char *)mem_malloc(32 * sizeof(char));
    strcpy(owner->group->name, "Engineering");
    owner->user = NULL;

    *state = owner;

    return 0;
}

static int test_itkc_getOwningGroup_tearDown(void **state)
{
    itk_Owner *_owner = (itk_Owner *)(*state);
    free(_owner->group->name);
    free(_owner->group);
    free(_owner);

    return 0;
}

static void test_itkc_getOwner_askOwnerNoOk(void **state)
{
    itk_Item _item;
    (void)state;

    _item.itk_ref = 101010;

    expect_value(proxy_POM_ask_owner, item, 101010);
    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "(%d) Error when getting ownership from item [%s].");

    will_return(proxy_POM_ask_owner, 0);
    will_return(proxy_POM_ask_owner, 0);
    will_return(proxy_POM_ask_owner, 1);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_noAllocationForOwner(void **state)
{
    itk_Item _item;
    (void)state;

    _item.itk_ref = 101010;

    expect_value(proxy_POM_ask_owner, item, 101010);
    expect_function_call(mock_malloc);
    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Error when allocating memory for object Owner.");
    expect_value(mock_malloc, size, sizeof(itk_Owner));

    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);
    will_return(mock_malloc, NULL);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_noAllocationForUser(void **state)
{
    itk_Item _item;
    itk_Owner *_owner;
    (void)state;

    _item.itk_ref = 101010;

    _owner = (itk_Owner *)malloc(sizeof(itk_Owner));

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_Owner));
    will_return(mock_malloc, _owner);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_User));
    will_return(mock_malloc, NULL);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Not allocated memory for object User.");

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Error when allocating memory for object User within Owner.");

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_askUserIdNoOk(void **state)
{
    itk_Item _item;
    itk_Owner *_owner;
    itk_User *_user;
    char *_userId;
    (void)state;

    _item.itk_ref = 101010;
    _userId = (char *)malloc(32 * sizeof(char));
    strcpy(_userId, "");
    _owner = (itk_Owner *)malloc(sizeof(itk_Owner));
    _user = (itk_User *)malloc(sizeof(itk_User));

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, ITK_ok);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_Owner));
    will_return(mock_malloc, _owner);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_User));
    will_return(mock_malloc, _user);

    expect_value(proxy_POM_ask_user_id, user, 101020);
    will_return(proxy_POM_ask_user_id, _userId);
    will_return(proxy_POM_ask_user_id, !ITK_ok);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "(%d) Error when getting the id from owning user.");

    expect_function_calls(proxy_MEM_free, 2);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_askUserNameNoOk(void **state)
{
    char *_userId;
    char *_userName;
    itk_Item _item;
    itk_Owner *_owner;
    itk_User *_user;
    (void)state;

    _item.itk_ref = 101010;
    _userId = (char *)malloc(32 * sizeof(char));
    strcpy(_userId, "000123");
    _userName = (char *)malloc(32 * sizeof(char));
    strcpy(_userName, "");
    _owner = (itk_Owner *)malloc(sizeof(itk_Owner));
    _user = (itk_User *)malloc(sizeof(itk_User));

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_Owner));
    will_return(mock_malloc, _owner);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_User));
    will_return(mock_malloc, _user);

    expect_value(proxy_POM_ask_user_id, user, 101020);
    will_return(proxy_POM_ask_user_id, _userId);
    will_return(proxy_POM_ask_user_id, ITK_ok);

    expect_value(proxy_POM_ask_user_name, user, 101020);
    will_return(proxy_POM_ask_user_name, _userName);
    will_return(proxy_POM_ask_user_name, !ITK_ok);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "(%d) Error when getting the name from owning user.");

    expect_function_calls(proxy_MEM_free, 2);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_noAllocationForGroup(void **state)
{
    char *_userId;
    char *_userName;
    itk_Item _item;
    itk_Owner *_owner;
    itk_User *_user;
    (void)state;

    _item.itk_ref = 101010;

    _userId = (char *)malloc(32 * sizeof(char));
    strcpy(_userId, "000123");
    _userName = (char *)malloc(32 * sizeof(char));
    strcpy(_userName, "Max Mustermann");
    _owner = (itk_Owner *)malloc(sizeof(itk_Owner));
    _user = (itk_User *)malloc(sizeof(itk_User));

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_Owner));
    will_return(mock_malloc, _owner);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_User));
    will_return(mock_malloc, _user);

    expect_value(proxy_POM_ask_user_id, user, 101020);
    will_return(proxy_POM_ask_user_id, _userId);
    will_return(proxy_POM_ask_user_id, ITK_ok);

    expect_value(proxy_POM_ask_user_name, user, 101020);
    will_return(proxy_POM_ask_user_name, _userName);
    will_return(proxy_POM_ask_user_name, ITK_ok);

    expect_function_call(mock_malloc);
    expect_value(mock_malloc, size, sizeof(itk_Group));
    will_return(mock_malloc, NULL);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Not allocated memory for object Group.");

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "Error when allocating memory for object Group within Owner.");

    expect_function_calls(proxy_MEM_free, 2);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner_askGroupNameNoOk(void **state)
{
    itk_Item _item;
    char *_itemId;
    char *_userName;
    char *_groupName;
    (void)state;

    _item.itk_ref = 101010;

    _itemId = (char *)malloc(32 * sizeof(char));
    strcpy(_itemId, "000123");
    _userName = (char *)malloc(32 * sizeof(char));
    strcpy(_userName, "Max Mustermann");
    _groupName = (char *)malloc(32 * sizeof(char));
    strcpy(_groupName, "");

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);

    expect_value(proxy_POM_ask_user_id, user, 101020);
    will_return(proxy_POM_ask_user_id, _itemId);
    will_return(proxy_POM_ask_user_id, ITK_ok);

    expect_value(proxy_POM_ask_user_name, user, 101020);
    will_return(proxy_POM_ask_user_name, _userName);
    will_return(proxy_POM_ask_user_name, ITK_ok);

    expect_value(proxy_POM_ask_group_name, group, 101030);
    will_return(proxy_POM_ask_group_name, _groupName);
    will_return(proxy_POM_ask_group_name, !ITK_ok);

    expect_function_call(UTIL_log);
    expect_value(UTIL_log, logLevel, WARN);
    expect_string(UTIL_log, fmt, "(%d) Error when getting the name from owning group.");

    expect_function_calls(proxy_MEM_free, 3);

    assert_null(itkc_getOwner(&_item));
}

static void test_itkc_getOwner(void **state)
{
    itk_Item _item;
    itk_Owner *_owner;
    (void)state;

    _item.itk_ref = 101010;

    expect_value(proxy_POM_ask_owner, item, 101010);
    will_return(proxy_POM_ask_owner, 101020);
    will_return(proxy_POM_ask_owner, 101030);
    will_return(proxy_POM_ask_owner, 0);

    expect_value(proxy_POM_ask_user_id, user, 101020);
    will_return(proxy_POM_ask_user_id, "000123");
    will_return(proxy_POM_ask_user_id, ITK_ok);

    expect_value(proxy_POM_ask_user_name, user, 101020);
    will_return(proxy_POM_ask_user_name, "Max Mustermann");
    will_return(proxy_POM_ask_user_name, ITK_ok);

    expect_value(proxy_POM_ask_group_name, group, 101030);
    will_return(proxy_POM_ask_group_name, "Group Name");
    will_return(proxy_POM_ask_group_name, ITK_ok);

    _owner = itkc_getOwner(&_item);
    assert_non_null(_owner);
    assert_int_equal(101020, _owner->user->itk_ref);
    assert_string_equal("000123", _owner->user->id);
    assert_string_equal("Max Mustermann", _owner->user->name);
    assert_int_equal(101030, _owner->group->itk_ref);
    assert_string_equal("Group Name", _owner->group->name);

    free(_owner->user);
    free(_owner->group);
    free(_owner);
}

/*
 * Main function
 */
int main(void)
{
    const struct CMUnitTest tests_itkconnector[] = {
        cmocka_unit_test(test_itkc_item_getId_itemIsNull),
        cmocka_unit_test(test_itkc_item_getId_itemIsNotNull),
        cmocka_unit_test(test_itkc_item_getName_itemIsNull),
        cmocka_unit_test(test_itkc_item_getName_itemIsNotNull),
        cmocka_unit_test(test_itkc_item_getType_itemIsNull),
        cmocka_unit_test(test_itkc_item_getType_itemIsNotNull),
        cmocka_unit_test(test_itkc_item_getNumRevisions_itemIsNull),
        cmocka_unit_test(test_itkc_item_getNumRevisions_itemIsNotNull),
        cmocka_unit_test(test_itkc_user_getId_userIsNull),
        cmocka_unit_test(test_itkc_user_getId_userIsNotNull),
        cmocka_unit_test(test_itkc_user_getName_userIsNull),
        cmocka_unit_test(test_itkc_user_getName_userIsNotNull),
        cmocka_unit_test(test_itkc_group_getName_groupIsNull),
        cmocka_unit_test(test_itkc_group_getName_groupIsNotNull),
        cmocka_unit_test(test_itkc_getValueFromArgument),
        cmocka_unit_test_setup_teardown(test_itkc_getValueFromArgument_nullAllocation, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test(test_itkc_getValueFromArgument_nullValueForArgument),
        cmocka_unit_test(test_m_itkc_item_loadNumRevisions),
        cmocka_unit_test(test_m_itkc_item_loadNumRevisions_notOk),
        cmocka_unit_test(test_itkc_findItem_itemIdIsNull),
        cmocka_unit_test(test_itkc_findItem_itemIdIsEmpty),
        cmocka_unit_test(test_itkc_findItem_notOk),
        cmocka_unit_test(test_itkc_findItem_itemNotFound),
        cmocka_unit_test_setup_teardown(test_itkc_findItem_notAllocatedMemory, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test(test_itkc_findItem_nameNotOk),
        cmocka_unit_test(test_itkc_findItem_typeNotOk),
        cmocka_unit_test(test_itkc_findItem),
        cmocka_unit_test(test_itkc_freeItem_nullItem),
        cmocka_unit_test(test_itkc_freeItem),
        cmocka_unit_test(test_m_itkc_allocUser),
        cmocka_unit_test_setup_teardown(test_m_itkc_allocUser_nullAllocation, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test(test_m_itkc_freeUser),
        cmocka_unit_test(test_m_itkc_freeUser_nullObject),
        cmocka_unit_test(test_m_itkc_allocGroup),
        cmocka_unit_test_setup_teardown(test_m_itkc_allocGroup_nullAllocation, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test(test_m_itkc_freeGroup),
        cmocka_unit_test(test_m_itkc_freeGroup_nullObject),
        cmocka_unit_test(test_itkc_freeOwner),
        cmocka_unit_test(test_itkc_freeOwner_nullObject),
        cmocka_unit_test(test_itkc_getOwningUser_nullObject),
        cmocka_unit_test_setup_teardown(test_itkc_getOwningUser, test_itkc_getOwningUser_setUp, test_itkc_getOwningUser_tearDown),
        cmocka_unit_test(test_itkc_getOwningGroup_nullObject),
        cmocka_unit_test_setup_teardown(test_itkc_getOwningGroup, test_itkc_getOwningGroup_setUp, test_itkc_getOwningGroup_tearDown),
        cmocka_unit_test(test_itkc_getOwner_askOwnerNoOk),
        cmocka_unit_test_setup_teardown(test_itkc_getOwner_noAllocationForOwner, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test_setup_teardown(test_itkc_getOwner_noAllocationForUser, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test_setup_teardown(test_itkc_getOwner_askUserIdNoOk, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test_setup_teardown(test_itkc_getOwner_askUserNameNoOk, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test_setup_teardown(test_itkc_getOwner_noAllocationForGroup, mem_malloc_setUp, mem_malloc_tearDown),
        cmocka_unit_test(test_itkc_getOwner_askGroupNameNoOk),
        cmocka_unit_test(test_itkc_getOwner)};

    return cmocka_run_group_tests(tests_itkconnector, NULL, NULL);
}
