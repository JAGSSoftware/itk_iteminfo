/**
 * @file
 * @brief
 * @since 04-Sep-2017
 * @author José Alberto García Sánchez
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>

#define ITEM_ID_SIZE 32
#define ITEM_NAME_SIZE 256
#define ITEM_TYPE_SIZE 256

// Here it is included the source file under test
#include "itemInfo.c"

#define BUFFER_SIZE 256
/**
 * @brief Buffer string to test the output to standard output
 */
static char buffer[BUFFER_SIZE] = "\0";

/**
 * @brief mock function for memory allocation.
 */
void *m_memoryAllocation(size_t _size)
{
	check_expected(_size);

	return mock_ptr_type(void *);
}

/**
 * @brief mock function
 */
int write(const char *format, ...)
{
	int numCharacters;
	va_list args;
	va_start(args, format);

	numCharacters = vsprintf(buffer, format, args);

	va_end(args);

	return numCharacters;
}

/**
 * @brief Mock function
 */
itk_Item *itkc_findItem(const char *itemId)
{
	function_called();
	check_expected(itemId);

	return mock_ptr_type(itk_Item *);
}

/**
 * @brief Mock function
 */
itk_Owner *itkc_getOwner(const itk_Item *item)
{
	function_called();
	check_expected(item);

	return mock_ptr_type(itk_Owner *);
}

/**
 * @brief Mock function
 */
itk_User *itkc_getOwningUser(const itk_Owner *owner)
{
	function_called();
	check_expected(owner);

	return mock_ptr_type(itk_User *);
}

/**
 * @brief Mock function
 */
itk_Group *itkc_getOwningGroup(const itk_Owner *owner)
{
	function_called();
	check_expected(owner);

	return mock_ptr_type(itk_Group *);
}

/**
 * @brief Mock function
 */
const char *itkc_item_getId(const itk_Item *item)
{
	function_called();
	check_expected(item);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
const char *itkc_item_getName(const itk_Item *item)
{
	function_called();
	check_expected(item);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
const char *itkc_item_getType(const itk_Item *item)
{
	function_called();
	check_expected(item);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
int itkc_item_getNumRevisions(const itk_Item *item)
{
	function_called();
	check_expected(item);

	return mock_type(int);
}

/**
 * @brief Mock function
 */
const char *itkc_user_getId(const itk_User *user)
{
	function_called();
	check_expected(user);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
const char *itkc_user_getName(const itk_User *user)
{
	function_called();
	check_expected(user);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
const char *itkc_group_getName(const itk_Group *group)
{
	function_called();
	check_expected(group);

	return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
void itkc_freeItem(itk_Item *item)
{
	function_called();
	check_expected(item);
}

/**
 * @brief Mock function
 */
void itkc_freeOwner(itk_Owner *owner)
{
	function_called();
	check_expected(owner);
}

/*
 * Test cases
 */
static void test_ITEM_INFO_get(void **state)
{
	ItemInfo *_itemInfo;
	itk_Item *_item;
	itk_Owner *_owner;
	itk_User *_user;
	itk_Group *_group;
	(void)state;

	_item = (itk_Item *)malloc(32 * sizeof(char));
	_owner = (itk_Owner *)malloc(32 * sizeof(char));
	_user = (itk_User *)malloc(32 * sizeof(char));
	_group = (itk_Group *)malloc(32 * sizeof(char));

	expect_function_call(itkc_findItem);
	expect_string(itkc_findItem, itemId, "000012");
	will_return(itkc_findItem, _item);

	expect_function_call(itkc_getOwner);
	expect_any(itkc_getOwner, item);
	will_return(itkc_getOwner, _owner);

	expect_function_call(itkc_getOwningUser);
	expect_any(itkc_getOwningUser, owner);
	will_return(itkc_getOwningUser, _user);

	expect_function_call(itkc_getOwningGroup);
	expect_any(itkc_getOwningGroup, owner);
	will_return(itkc_getOwningGroup, _group);

	expect_function_call(itkc_freeItem);
	expect_any(itkc_freeItem, item);

	expect_function_call(itkc_freeOwner);
	expect_any(itkc_freeOwner, owner);

	_itemInfo = ITEM_INFO_get("000012");
	_user = itkc_getOwningUser(_itemInfo->owner);
	_group = itkc_getOwningGroup(_itemInfo->owner);

	assert_non_null(_itemInfo);

	ITEM_INFO_free(&_itemInfo);
	free(_item);
	free(_owner);
	free(_user);
	free(_group);
}

static int test_ITEM_INFO_get_noMemoryAllocation_setUp(void **state)
{
	(void)state;
	m_memAlloc = &m_memoryAllocation;
	return 0;
}

static int test_ITEM_INFO_get_noMemoryAllocation_tearDown(void **state)
{
	(void)state;
	m_memAlloc = &malloc;
	return 0;
}

static void test_ITEM_INFO_get_noMemoryAllocation(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	expect_value(m_memoryAllocation, _size, sizeof(ItemInfo));

	will_return(m_memoryAllocation, NULL);

	_itemInfo = ITEM_INFO_get("000123");

	assert_null(_itemInfo);
}

static void test_ITEM_INFO_get_noItemFound(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	expect_function_call(itkc_findItem);
	expect_string(itkc_findItem, itemId, "000123");
	will_return(itkc_findItem, NULL);

	_itemInfo = ITEM_INFO_get("000123");

	assert_null(_itemInfo);

	free(_itemInfo);
}

static void test_ITEM_INFO_free_nullObject(void **state)
{
	ItemInfo *_itemInfo = NULL;
	(void)state;

	ITEM_INFO_free(&_itemInfo);

	assert_null(_itemInfo);
}

static void test_ITEM_INFO_free_notFoundObject(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	_itemInfo = (ItemInfo *)malloc(sizeof(ItemInfo));

	expect_function_call(itkc_freeItem);
	expect_any(itkc_freeItem, item);

	expect_function_call(itkc_freeOwner);
	expect_any(itkc_freeOwner, owner);

	ITEM_INFO_free(&_itemInfo);

	assert_null(_itemInfo);
}

static void test_m_isItemInfoLoaded_nullItemInfo(void **state)
{
	(void)state;
	assert_false(m_isItemInfoLoaded(NULL));
}

static void test_m_isItemInfoLoaded_newlyCreatedItemInfo(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	_itemInfo = (ItemInfo *)malloc(sizeof(ItemInfo));

	expect_function_call(itkc_item_getNumRevisions);
	expect_any(itkc_item_getNumRevisions, item);
	will_return(itkc_item_getNumRevisions, -1);

	assert_false(m_isItemInfoLoaded(_itemInfo));

	free(_itemInfo);
}

static void test_m_isItemInfoLoaded_yesItIsLoaded(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	_itemInfo = (ItemInfo *)malloc(sizeof(ItemInfo));

	expect_function_call(itkc_item_getNumRevisions);
	expect_any(itkc_item_getNumRevisions, item);
	will_return(itkc_item_getNumRevisions, 1);

	assert_true(m_isItemInfoLoaded(_itemInfo));

	free(_itemInfo);
}

static int test_ITEM_INFO_write_setUp(void **state)
{
	(void)state;
	m_write = &write;
	memset(buffer, 0, BUFFER_SIZE * sizeof(char));

	return 0;
}

static int test_ITEM_INFO_write_tearDown(void **state)
{
	(void)state;
	m_write = &printf;

	return 0;
}

static void test_ITEM_INFO_write_itemInfoIsNull(void **state)
{
	ItemInfo *_itemInfo = NULL;
	(void)state;

	ITEM_INFO_write(_itemInfo);

	assert_string_equal("", buffer);

	ITEM_INFO_free(&_itemInfo);
}

static void test_ITEM_INFO_write_infoItemNotLoaded(void **state)
{
	ItemInfo *_itemInfo;
	(void)state;

	expect_function_call(itkc_item_getNumRevisions);
	expect_any(itkc_item_getNumRevisions, item);
	will_return(itkc_item_getNumRevisions, -1);

	expect_function_call(itkc_item_getId);
	expect_any(itkc_item_getId, item);
	will_return(itkc_item_getId, "000123");

	_itemInfo = (ItemInfo *)malloc(sizeof(ItemInfo));

	ITEM_INFO_write(_itemInfo);

	assert_string_equal("Item with id [000123] not found or not yet loaded.\n", buffer);

	free(_itemInfo);
}

static void test_ITEM_INFO_write_infoItemIsLoaded(void **state)
{
	ItemInfo *_itemInfo;
	itk_User *_user = NULL;
	itk_Group *_group = NULL;
	(void)state;

	_itemInfo = (ItemInfo *)malloc(sizeof(ItemInfo));

	expect_function_call(itkc_item_getNumRevisions);
	expect_any(itkc_item_getNumRevisions, item);
	will_return(itkc_item_getNumRevisions, 3);

	expect_function_call(itkc_getOwningUser);
	expect_any(itkc_getOwningUser, owner);
	will_return(itkc_getOwningUser, _user);

	expect_function_call(itkc_getOwningGroup);
	expect_any(itkc_getOwningGroup, owner);
	will_return(itkc_getOwningGroup, _group);

	expect_function_call(itkc_group_getName);
	expect_any(itkc_group_getName, group);
	will_return(itkc_group_getName, "Owning Group");

	expect_function_call(itkc_user_getName);
	expect_any(itkc_user_getName, user);
	will_return(itkc_user_getName, "user name #01");

	expect_function_call(itkc_user_getId);
	expect_any(itkc_user_getId, user);
	will_return(itkc_user_getId, "user01");

	expect_function_call(itkc_item_getNumRevisions);
	expect_any(itkc_item_getNumRevisions, item);
	will_return(itkc_item_getNumRevisions, 3);

	expect_function_call(itkc_item_getType);
	expect_any(itkc_item_getType, item);
	will_return(itkc_item_getType, "item type v2.0");

	expect_function_call(itkc_item_getName);
	expect_any(itkc_item_getName, item);
	will_return(itkc_item_getName, "item name");

	expect_function_call(itkc_item_getId);
	expect_any(itkc_item_getId, item);
	will_return(itkc_item_getId, "000123");

	ITEM_INFO_write(_itemInfo);

	assert_string_equal("item.id = [000123] ->\n\
\titem.name = [item name]\n\
\titem.type = [item type v2.0]\n\
\titem.numRevs = [3]\n\
\tuser.id = [user01]\n\
\tuser.name = [user name #01]\n\
\tgroup.name = [Owning Group]\n",
						buffer);

	free(_itemInfo);
}

int main(void)
{
	const struct CMUnitTest tests_infoItem[] = {
		cmocka_unit_test(test_ITEM_INFO_get),
		cmocka_unit_test_setup_teardown(test_ITEM_INFO_get_noMemoryAllocation,
										test_ITEM_INFO_get_noMemoryAllocation_setUp, test_ITEM_INFO_get_noMemoryAllocation_tearDown),
		cmocka_unit_test(test_ITEM_INFO_get_noItemFound),
		cmocka_unit_test(test_ITEM_INFO_free_nullObject),
		cmocka_unit_test(test_ITEM_INFO_free_notFoundObject),
		cmocka_unit_test(test_m_isItemInfoLoaded_nullItemInfo),
		cmocka_unit_test(test_m_isItemInfoLoaded_newlyCreatedItemInfo),
		cmocka_unit_test(test_m_isItemInfoLoaded_yesItIsLoaded),
		cmocka_unit_test_setup_teardown(test_ITEM_INFO_write_itemInfoIsNull, test_ITEM_INFO_write_setUp, test_ITEM_INFO_write_tearDown),
		cmocka_unit_test_setup_teardown(test_ITEM_INFO_write_infoItemNotLoaded, test_ITEM_INFO_write_setUp, test_ITEM_INFO_write_tearDown),
		cmocka_unit_test_setup_teardown(test_ITEM_INFO_write_infoItemIsLoaded, test_ITEM_INFO_write_setUp, test_ITEM_INFO_write_tearDown)};

	return cmocka_run_group_tests(tests_infoItem, NULL, NULL);
}
