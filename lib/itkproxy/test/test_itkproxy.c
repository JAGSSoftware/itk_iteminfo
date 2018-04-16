/**
 * @file
 * @brief
 * @since 01-Sep-2017
 * @author José Alberto García Sánchez
 */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// Here is included the source file under test
#include "itkproxy.c"

/**
 * @brief Mock function
 */
char *mock_ITK_ask_cli_argument(const char *key)
{
    check_expected(key);

    return mock_ptr_type(char *);
}

/**
 * @brief Mock function
 */
void mock_MEM_free(void *ptr)
{
    function_called();
    check_expected(ptr);
}

/**
 * @brief Mock function
 */
void mock_TC_write_syslog(const char *message, ...)
{
    function_called();
    check_expected(message);
}

/**
 * @brief Mock function
 */
int mock_ITK_auto_login(void)
{
    function_called();
    return mock_type(int);
}

/**
 * @brief Mock function
 */
int mock_ITK_exit_module(const logical ignoreUnsavedStuff)
{
    function_called();
    check_expected(ignoreUnsavedStuff);
    return mock_type(int);
}

/*
 * Unit tests
 */
static void test_proxy_ITK_auto_login(void **state)
{
    (void)state;

    expect_function_call(mock_ITK_auto_login);
    will_return(mock_ITK_auto_login, 0);

    assert_int_equal(0, proxy_ITK_auto_login());
}

static int setUp_proxy_ITK_auto_login(void **state)
{
    (void)state;

    f_ITK_auto_login = &mock_ITK_auto_login;

    return 0;
}

static int tearDown_proxy_ITK_auto_login(void **state)
{
    (void)state;

    f_ITK_auto_login = &ITK_auto_login;

    return 0;
}

static void test_proxy_ITK_exit_module(void **state)
{
    (void)state;

    expect_function_call(mock_ITK_exit_module);
    expect_value(mock_ITK_exit_module, ignoreUnsavedStuff, false);
    will_return(mock_ITK_exit_module, 0);

    assert_int_equal(0, proxy_ITK_exit_module(false));
}

static int setUp_proxy_ITK_exit_module(void **state)
{
    (void)state;

    f_ITK_exit_module = &mock_ITK_exit_module;

    return 0;
}

static int tearDown_proxy_ITK_exit_module(void **state)
{
    (void)state;

    f_ITK_exit_module = &ITK_exit_module;

    return 0;
}

static void test_proxy_ITK_ask_cli_argument(void **state)
{
    char *_value;
    (void)state;

    expect_string(mock_ITK_ask_cli_argument, key, "key");

    will_return(mock_ITK_ask_cli_argument, "value");

    _value = proxy_ITK_ask_cli_argument("key");

    assert_string_equal("value", _value);
}

static int setUp_proxy_ITK_ask_cli_argument(void **state)
{
    (void)state;
    f_ITK_ask_cli_argument = &mock_ITK_ask_cli_argument;

    return 0;
}

static int tearDown_proxy_ITK_ask_cli_argument(void **state)
{
    (void)state;

    return 0;
}

static void test_proxy_MEM_free(void **state)
{
    (void)state;

    expect_value(mock_MEM_free, ptr, *state);
    expect_function_call(mock_MEM_free);

    proxy_MEM_free(*state);
}

static int setUp_proxy_MEM_free(void **state)
{
    (void)state;
    f_MEM_free = &mock_MEM_free;

    return 0;
}

static int tearDown_proxy_MEM_free(void **state)
{
    (void)state;
    f_MEM_free = &MEM_free;

    return 0;
}

static void test_proxy_TC_write_syslog(void **state)
{
    (void)state;

    expect_function_call(mock_TC_write_syslog);
    expect_string(mock_TC_write_syslog, message, "[TRACE] - 20170223: (522323)This is an example");

    proxy_TC_write_syslog("[%s] - 20170223: (%d)%s", "TRACE", 522323, "This is an example");
}

static int setUp_proxy_TC_write_syslog(void **state)
{
    (void)state;
    f_TC_write_syslog = &mock_TC_write_syslog;

    return 0;
}

static int tearDown_proxy_TC_write_syslog(void **state)
{
    (void)state;
    f_TC_write_syslog = &TC_write_syslog;

    return 0;
}

int main(void)
{
    const struct CMUnitTest tests_itkproxy[] = {
        cmocka_unit_test_setup_teardown(test_proxy_ITK_auto_login, setUp_proxy_ITK_auto_login, tearDown_proxy_ITK_auto_login),
        cmocka_unit_test_setup_teardown(test_proxy_ITK_exit_module, setUp_proxy_ITK_exit_module, tearDown_proxy_ITK_exit_module),
        cmocka_unit_test_setup_teardown(test_proxy_ITK_ask_cli_argument, setUp_proxy_ITK_ask_cli_argument, tearDown_proxy_ITK_ask_cli_argument),
        cmocka_unit_test_setup_teardown(test_proxy_MEM_free, setUp_proxy_MEM_free, tearDown_proxy_MEM_free),
        cmocka_unit_test_setup_teardown(test_proxy_TC_write_syslog, setUp_proxy_TC_write_syslog, tearDown_proxy_TC_write_syslog)};

    return cmocka_run_group_tests(tests_itkproxy, NULL, NULL);
}
