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
#include "main.cpp"

/**
 * @brief Mock function
 */
ItemInfo *ITEM_INFO_get(char const *itemId)
{
	function_called();
	check_expected(itemId);
	return mock_ptr_type(ItemInfo *);
}

/**
 * @brief Mock function
 */
void ITEM_INFO_write(const ItemInfo *itemInfo)
{
	function_called();
	check_expected(itemInfo);
}

/**
 * @brief Mock function
 */
void ITEM_INFO_free(ItemInfo **itemInfo)
{
	function_called();
	check_expected_ptr(*itemInfo);
}

/**
 * @brief Mock function
 */
boolean readArguments(void)
{
	function_called();
	return mock_type(boolean);
}

/**
 * @brief Mock function
 */
void freeArguments(void)
{
	function_called();
}

/**
 * @brief Mock function
 */
const char *getItemId(void)
{
	function_called();
	return mock_type(char *);
}

/**
 * @brief Mock function
 */
unsigned int ENV_isSetEnvironmentVariable(const char *varName)
{
	function_called();
	check_expected(varName);
	return mock_type(unsigned int);
}

/**
 * @brief Mock function
 */
void proxy_TC_write_syslog(const char *message, ...)
{
	function_called();
	check_expected(message);
}

/**
 * @brief Mock function
 */
int proxy_ITK_auto_login(void)
{
	function_called();
	return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_ITK_exit_module(const boolean ignoreUnsavedStuff)
{
	function_called();
	check_expected(ignoreUnsavedStuff);
	return mock_type(int);
}

/**
 * @brief Mock function
 */
int proxy_POM_init_module(void)
{
	function_called();
	return mock_type(int);
}

/**
 * @brief Mock function
 */
void UTIL_setLogLevel(LogLevel logLevel)
{
	function_called();
	check_expected(logLevel);
}

/**
 * @brief Mock function
 */
void UTIL_setLoggerFunction(int (*function)(const char *))
{
	function_called();
	check_expected_ptr(function);
}

/**
 * @brief Mock function
 */
void UTIL_setAppendLineCarrier(unsigned int append)
{
	function_called();
	check_expected(append);
}

/**
 * @brief Mock function
 */
void UTIL_log(LogLevel logLevel, const char *fmt, ...)
{
	function_called();
	check_expected(logLevel);
	check_expected(fmt);
}

/*
 * Test cases
 */
static void test_areRequiredEnvironmentVariablesSet_none(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, false);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcDbConnect(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, false);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcRoot(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, false);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcData(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcDbConnectAndTcRoot(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, false);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcDbConnectAndTcData(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_tcRootAndTcData(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	assert_false(areRequiredEnvironmentVariablesSet());
}

static void test_areRequiredEnvironmentVariablesSet_all(void **state)
{
	(void)state;

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	assert_true(areRequiredEnvironmentVariablesSet());
}

static void test_configureLogger(void **state)
{
	(void)state;
	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	configureLogger();
}

static void test_myLogger(void **state)
{
	(void)state;

	expect_function_call(proxy_TC_write_syslog);
	expect_string(proxy_TC_write_syslog, message, "Hello, world...");

	myLogger("Hello, world...");
}

static void test_ITK_user_main_envVariablesNotSet(void **state)
{
	char *argp[] = {"-itemId=000012"};
	(void)state;

	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);
	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, false);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, INFO);
	expect_string(UTIL_log, fmt, "Missing required environment variables");

	assert_int_equal(-1, ITK_user_main(2, argp));
}

static void test_ITK_user_main_errorByReadArguments(void **state)
{
	char *argp[] = {"-itemId=000012"};
	(void)state;

	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);
	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_function_call(readArguments);
	will_return(readArguments, false);

	expect_function_call(freeArguments);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, ERROR);
	expect_string(UTIL_log, fmt, "Error reading the arguments.");

	expect_function_call(proxy_ITK_exit_module);
	expect_value(proxy_ITK_exit_module, ignoreUnsavedStuff, false);
	will_return(proxy_ITK_exit_module, 0);

	assert_int_equal(-1, ITK_user_main(2, argp));
}

static void test_ITK_user_main_errorByAutoLogin(void **state)
{
	char *argp[] = {"-itemId=000012"};
	(void)state;

	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);
	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_function_call(readArguments);
	will_return(readArguments, true);

	expect_function_call(proxy_ITK_auto_login);
	will_return(proxy_ITK_auto_login, 1);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, WARN);
	expect_string(UTIL_log, fmt, "Error when auto logging in.");

	expect_function_call(proxy_ITK_exit_module);
	expect_value(proxy_ITK_exit_module, ignoreUnsavedStuff, false);
	will_return(proxy_ITK_exit_module, 0);

	expect_function_call(freeArguments);

	assert_int_equal(-1, ITK_user_main(2, argp));
}

static void test_ITK_user_main_itemInfoNotFound(void **state)
{
	char *argp[] = {"-itemId=000012"};
	(void)state;

	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);
	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_function_call(readArguments);
	will_return(readArguments, true);

	expect_function_call(proxy_ITK_auto_login);
	will_return(proxy_ITK_auto_login, 0);

	expect_function_call(proxy_POM_init_module);
	will_return(proxy_POM_init_module, 0);

	expect_function_call(getItemId);
	will_return(getItemId, "000123");

	expect_function_call(ITEM_INFO_get);
	expect_string(ITEM_INFO_get, itemId, "000123");
	will_return(ITEM_INFO_get, NULL);

	expect_function_call(freeArguments);

	expect_function_call(proxy_ITK_exit_module);
	expect_value(proxy_ITK_exit_module, ignoreUnsavedStuff, false);
	will_return(proxy_ITK_exit_module, 0);

	assert_int_equal(0, ITK_user_main(2, argp));
}

static void test_ITK_user_main_itemInfoFound(void **state)
{
	char *argp[] = {"-itemId=000012"};
	ItemInfo *_itemInfo;
	(void)state;

	expect_function_call(UTIL_setLogLevel);
	expect_value(UTIL_setLogLevel, logLevel, INFO);

	expect_function_call(UTIL_setLoggerFunction);
	expect_value(UTIL_setLoggerFunction, function, &myLogger);

	expect_function_call(UTIL_setAppendLineCarrier);
	expect_value(UTIL_setAppendLineCarrier, append, true);

	expect_function_call(UTIL_log);
	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, fmt, "Checking the required environment variables");

	expect_function_calls(ENV_isSetEnvironmentVariable, 3);
	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DB_CONNECT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_ROOT");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_string(ENV_isSetEnvironmentVariable, varName, "TC_DATA");
	will_return(ENV_isSetEnvironmentVariable, true);

	expect_function_call(readArguments);
	will_return(readArguments, true);

	expect_function_call(proxy_ITK_auto_login);
	will_return(proxy_ITK_auto_login, 0);

	expect_function_call(proxy_POM_init_module);
	will_return(proxy_POM_init_module, 0);

	expect_function_call(getItemId);
	will_return(getItemId, "000123");

	expect_function_call(ITEM_INFO_get);
	expect_string(ITEM_INFO_get, itemId, "000123");
	will_return(ITEM_INFO_get, _itemInfo);

	expect_function_call(ITEM_INFO_write);
	expect_value(ITEM_INFO_write, itemInfo, _itemInfo);

	expect_function_call(ITEM_INFO_free);
	expect_value(ITEM_INFO_free, *itemInfo, _itemInfo);

	expect_function_call(freeArguments);

	expect_function_call(proxy_ITK_exit_module);
	expect_value(proxy_ITK_exit_module, ignoreUnsavedStuff, false);
	will_return(proxy_ITK_exit_module, 0);

	assert_int_equal(0, ITK_user_main(2, argp));
}

int main(void)
{
	const struct CMUnitTest tests_main[] = {
		cmocka_unit_test(test_configureLogger),
		cmocka_unit_test(test_myLogger),
		// areRequiredEnvironmentVariablesSet()
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_none),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcDbConnect),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcRoot),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcData),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcDbConnectAndTcRoot),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcDbConnectAndTcData),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_tcRootAndTcData),
		cmocka_unit_test(test_areRequiredEnvironmentVariablesSet_all),
		// ITK_user_main
		cmocka_unit_test(test_ITK_user_main_envVariablesNotSet),
		cmocka_unit_test(test_ITK_user_main_errorByReadArguments),
		cmocka_unit_test(test_ITK_user_main_errorByAutoLogin),
		cmocka_unit_test(test_ITK_user_main_itemInfoNotFound),
		cmocka_unit_test(test_ITK_user_main_itemInfoFound)};

	return cmocka_run_group_tests(tests_main, NULL, NULL);
}
