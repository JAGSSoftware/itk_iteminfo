/**
 * @file
 * @brief
 * @since 25-Jan-2018
 * @author José Alberto García Sánchez
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>
#include <string.h>

// File under test
#include "itkproxy_pom.c"

/**
 * @brief Mock function
 */
int mock_POM_init_module(void)
{
    function_called();
    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_POM_ask_owner(tag_t item, tag_t *user, tag_t *group)
{
    check_expected(item);
    check_expected(*user);
    check_expected(*group);

    *user = mock_type(tag_t);
    *group = mock_type(tag_t);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_POM_ask_user_id(tag_t user, char **id)
{
    char *_mockId = mock_ptr_type(char *);
    check_expected(user);
    check_expected_ptr(*id);

    *id = (char *)malloc((strlen(_mockId) + 1) * sizeof(char));
    strcpy(*id, _mockId);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_POM_ask_user_name(tag_t user, char **name)
{
    char *_mockName = mock_ptr_type(char *);
    check_expected(user);
    check_expected(*name);

    *name = (char *)malloc((strlen(_mockName) + 1) * sizeof(char));
    strcpy(*name, _mockName);

    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_POM_ask_group_name(tag_t group, char **name)
{
    char *_mockName = mock_ptr_type(char *);
    check_expected(group);
    check_expected(*name);

    *name = (char *)malloc((strlen(_mockName) + 1) * sizeof(char));
    strcpy(*name, _mockName);

    return mock_type(int);
}

/*
 * Test cases
 */
static void test_proxy_POM_init_module(void **state)
{
    (void)state;

    expect_function_call(mock_POM_init_module);
    will_return(mock_POM_init_module, 0);

    assert_int_equal(0, proxy_POM_init_module());
}

static int setUp_proxy_POM_init_module(void **state)
{
    (void)state;
    f_POM_init_module = &mock_POM_init_module;
    return 0;
}

static void test_proxy_POM_ask_owner(void **state)
{
    tag_t _item = 10;
    tag_t _user = NULL_TAG;
    tag_t _group = NULL_TAG;
    int _status = -1;
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_POM_ask_owner, item, 10);
    expect_value(mock_POM_ask_owner, *user, NULL_TAG);
    expect_value(mock_POM_ask_owner, *group, NULL_TAG);

    will_return(mock_POM_ask_owner, 20);
    will_return(mock_POM_ask_owner, 30);
    will_return(mock_POM_ask_owner, 0);

    _status = proxy_POM_ask_owner(_item, &_user, &_group);

    assert_int_equal(0, _status);
    assert_int_equal(20, _user);
    assert_int_equal(30, _group);
}

static int setUp_proxy_POM_ask_owner(void **state)
{
    (void)state;
    f_POM_ask_owner = &mock_POM_ask_owner;

    return 0;
}

static void test_proxy_POM_ask_user_id(void **state)
{
    tag_t _user = 10;
    char *_id = NULL;
    int _status = -1;
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_POM_ask_user_id, user, 10);
    expect_value(mock_POM_ask_user_id, *id, NULL);

    will_return(mock_POM_ask_user_id, "010203");
    will_return(mock_POM_ask_user_id, 0);

    _status = proxy_POM_ask_user_id(_user, &_id);

    assert_int_equal(0, _status);
    assert_string_equal("010203", _id);

    free(_id);
}

static int setUp_proxy_POM_ask_user_id(void **state)
{
    (void)state;
    f_POM_ask_user_id = &mock_POM_ask_user_id;

    return 0;
}

static void test_proxy_POM_ask_user_name(void **state)
{
    tag_t _user = 10;
    char *_name = NULL;
    int _status = -1;
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_POM_ask_user_name, user, 10);
    expect_value(mock_POM_ask_user_name, *name, NULL);

    will_return(mock_POM_ask_user_name, "User Name");
    will_return(mock_POM_ask_user_name, 0);

    _status = proxy_POM_ask_user_name(_user, &_name);

    assert_int_equal(0, _status);
    assert_string_equal("User Name", _name);

    free(_name);
}

static int setUp_proxy_POM_ask_user_name(void **state)
{
    (void)state;
    f_POM_ask_user_name = &mock_POM_ask_user_name;

    return 0;
}

static void test_proxy_POM_ask_group_name(void **state)
{
    tag_t _group = 10;
    char *_name = NULL;
    int _status = -1;
    (void)state;

    assert_int_not_equal(0, _status);
    expect_value(mock_POM_ask_group_name, group, 10);
    expect_value(mock_POM_ask_group_name, *name, NULL);

    will_return(mock_POM_ask_group_name, "Group Name");
    will_return(mock_POM_ask_group_name, 0);

    _status = proxy_POM_ask_group_name(_group, &_name);

    assert_int_equal(0, _status);
    assert_string_equal("Group Name", _name);

    free(_name);
}

static int setUp_proxy_POM_ask_group_name(void **state)
{
    (void)state;
    f_POM_ask_group_name = &mock_POM_ask_group_name;

    return 0;
}

int main(void)
{
    const struct CMUnitTest tests_itkproxy_pom[] = {
        cmocka_unit_test_setup(test_proxy_POM_init_module, setUp_proxy_POM_init_module),
        cmocka_unit_test_setup(test_proxy_POM_ask_owner, setUp_proxy_POM_ask_owner),
        cmocka_unit_test_setup(test_proxy_POM_ask_user_id, setUp_proxy_POM_ask_user_id),
        cmocka_unit_test_setup(test_proxy_POM_ask_user_name, setUp_proxy_POM_ask_user_name),
        cmocka_unit_test_setup(test_proxy_POM_ask_group_name, setUp_proxy_POM_ask_group_name)};

    return cmocka_run_group_tests(tests_itkproxy_pom, NULL, NULL);
}
