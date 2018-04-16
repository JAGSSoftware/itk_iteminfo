/**
 * @file
 * @brief
 * @since 24-Jan-2018
 * @author José Alberto García Sánchez
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include <stdlib.h>

// Here is included the source file under test
#include "itkproxy_item.c"

/**
 * @brief Mock function
 */
int mock_ITEM_ask_name(tag_t item, char *name)
{
    check_expected(item);
    check_expected(name);

    strcpy(name, mock_ptr_type(char *));

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_ITEM_ask_type(tag_t item, char *type)
{
    check_expected(item);
    check_expected(type);

    strcpy(type, mock_ptr_type(char *));

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_ITEM_list_all_revs(tag_t item, int *count, tag_t **revisions)
{
    int i = -1;
    check_expected(item);
    check_expected(*count);
    check_expected_ptr(revisions);

    *count = mock_type(int);
    *revisions = (tag_t *)malloc((*count) * sizeof(tag_t));
    for (i = 0; i < *count; i++)
    {
        (*revisions)[i] = mock_type(tag_t);
    }

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_ITEM_find_items_by_key_attributes(int numAttributes, const char **attributeNames, const char **attributeValues, int *numItems, tag_t **itemTags)
{
    int i;
    check_expected(numAttributes);
    check_expected_ptr(attributeNames[0]);
    check_expected_ptr(attributeValues[0]);
    check_expected(*numItems);
    check_expected_ptr(*itemTags);

    *numItems = mock_type(int);
    *itemTags = (tag_t *)malloc((*numItems) * sizeof(tag_t));
    for (i = 0; i < *numItems; i++)
    {
        (*itemTags)[i] = mock_type(tag_t);
    }

    return mock_type(int);
}

/*
 * Test cases
 */
static void test_itkproxy_item_allocId(void **state)
{
    char *_id = NULL;
    (void)state;

    assert_null(_id);
    _id = itkproxy_item_allocId();

    assert_non_null(_id);

    free(_id);
}

static void test_itkproxy_item_allocName(void **state)
{
    char *_name = NULL;
    (void)state;

    assert_null(_name);
    _name = itkproxy_item_allocName();

    assert_non_null(_name);

    free(_name);
}

static void test_itkproxy_item_allocType(void **state)
{
    char *_type = NULL;
    (void)state;

    assert_null(_type);
    _type = itkproxy_item_allocType();

    assert_non_null(_type);

    free(_type);
}

static void test_proxy_ITEM_ask_name(void **state)
{
    tag_t _item = 13;
    int _status = -1;
    char _name[ITEM_name_size_c + 1] = "\0";
    (void)state;

    assert_int_not_equal(0, _status);

    expect_value(mock_ITEM_ask_name, item, _item);
    expect_string(mock_ITEM_ask_name, name, "\0");

    will_return(mock_ITEM_ask_name, "item name");
    will_return(mock_ITEM_ask_name, 0);

    _status = proxy_ITEM_ask_name(_item, _name);

    assert_int_equal(0, _status);
    assert_string_equal("item name", _name);
}

static int setUp_proxy_ITEM_ask_name(void **state)
{
    (void)state;
    f_ITEM_ask_name = &mock_ITEM_ask_name;

    return 0;
}

static void test_proxy_ITEM_ask_type(void **state)
{
    tag_t _item = 13;
    int _status = -1;
    char _type[ITEM_type_size_c + 1] = "\0";
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_ITEM_ask_type, item, _item);
    expect_string(mock_ITEM_ask_type, type, "\0");

    will_return(mock_ITEM_ask_type, "item revision");
    will_return(mock_ITEM_ask_type, 0);

    _status = proxy_ITEM_ask_type(_item, _type);

    assert_int_equal(0, _status);
    assert_string_equal("item revision", _type);
}

static int setUp_proxy_ITEM_ask_type(void **state)
{
    (void)state;
    f_ITEM_ask_type = &mock_ITEM_ask_type;

    return 0;
}

static void test_proxy_ITEM_list_all_revs(void **state)
{
    tag_t _item = 12;
    int _count = -1;
    tag_t *_revisions = NULLTAG;
    int _status = -1;
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_ITEM_list_all_revs, item, _item);
    expect_value(mock_ITEM_list_all_revs, *count, _count);
    expect_value(mock_ITEM_list_all_revs, revisions, &_revisions);

    will_return(mock_ITEM_list_all_revs, 2);
    will_return(mock_ITEM_list_all_revs, 10);
    will_return(mock_ITEM_list_all_revs, 20);
    will_return(mock_ITEM_list_all_revs, 0);

    _status = proxy_ITEM_list_all_revs(_item, &_count, &_revisions);

    assert_int_equal(0, _status);
    assert_int_equal(2, _count);

    free(_revisions);
}

static int setUp_proxy_ITEM_list_all_revs(void **state)
{
    (void)state;
    f_ITEM_list_all_revs = &mock_ITEM_list_all_revs;

    return 0;
}

static void test_proxy_ITEM_find_items_by_key_attributes(void **state)
{
    int _numItems = -1;
    tag_t *_itemTags = NULL;
    int _status = -1;
    const char *_attributeNames[1] = {"item_id"};
    const char *_attributeValues[1] = {"010203"};
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_ITEM_find_items_by_key_attributes, numAttributes, 1);
    expect_string(mock_ITEM_find_items_by_key_attributes, attributeNames[0], "item_id");
    expect_string(mock_ITEM_find_items_by_key_attributes, attributeValues[0], "010203");
    expect_value(mock_ITEM_find_items_by_key_attributes, *numItems, -1);
    expect_value(mock_ITEM_find_items_by_key_attributes, *itemTags, NULL);

    will_return(mock_ITEM_find_items_by_key_attributes, 1);
    will_return(mock_ITEM_find_items_by_key_attributes, 10);
    will_return(mock_ITEM_find_items_by_key_attributes, 0);

    _status = proxy_ITEM_find_items_by_key_attributes(1, _attributeNames, _attributeValues, &_numItems, &_itemTags);

    assert_int_equal(0, _status);
    assert_int_equal(1, _numItems);
    assert_int_equal(10, _itemTags[0]);

    free(_itemTags);
}

static int setUp_proxy_ITEM_find_items_by_key_attributes(void **state)
{
    (void)state;
    f_ITEM_find_items_by_key_attributes = &mock_ITEM_find_items_by_key_attributes;

    return 0;
}

int main(void)
{
    const struct CMUnitTest tests_itkproxy_item[] = {
        cmocka_unit_test(test_itkproxy_item_allocId),
        cmocka_unit_test(test_itkproxy_item_allocName),
        cmocka_unit_test(test_itkproxy_item_allocType),
        cmocka_unit_test_setup(test_proxy_ITEM_ask_name, setUp_proxy_ITEM_ask_name),
        cmocka_unit_test_setup(test_proxy_ITEM_ask_type, setUp_proxy_ITEM_ask_type),
        cmocka_unit_test_setup(test_proxy_ITEM_list_all_revs, setUp_proxy_ITEM_list_all_revs),
        cmocka_unit_test_setup(test_proxy_ITEM_find_items_by_key_attributes, setUp_proxy_ITEM_find_items_by_key_attributes)};

    return cmocka_run_group_tests(tests_itkproxy_item, NULL, NULL);
}
