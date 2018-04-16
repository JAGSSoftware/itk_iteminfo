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

#include <stdio.h>

// Here it is included the source file under test
#include "arguments.c"

static char logMessage[256] = "\0";

/**
 * @brief mock function
 */
void UTIL_log(const LogLevel _logLevel, const char *_message, ...)
{
	va_list args;
	va_start(args, _message);

	vsprintf(logMessage, _message, args);

	check_expected(_logLevel);
	check_expected(_message);

	va_end(args);
}

/**
 * @brief mock function
 */
void *mock_malloc(size_t _Size)
{
	(void)_Size;

	return mock_ptr_type(void *);
}

/**
 * @brief Mock function
 */
char *itkc_getValueFromArgument(const char *key)
{
	check_expected(key);

	return mock_ptr_type(char *);
}

/*
 * Test cases
 */
static void test_readArguments_noAllocation(void **state)
{
	(void)state;

	expect_value(UTIL_log, _logLevel, ERROR);
	expect_string(UTIL_log, _message, "Error when creating Arguments.");

	will_return(mock_malloc, NULL);

	assert_null(m_arguments);
	assert_false(readArguments());
}

static void test_readArguments_noArgumentProvided(void **state)
{
	Arguments arguments;
	(void)state;

	expect_value(UTIL_log, _logLevel, WARN);
	expect_string(UTIL_log, _message, "argument [%s] has not been provided");
	expect_string(itkc_getValueFromArgument, key, "itemId");

	will_return(mock_malloc, &arguments);
	will_return(itkc_getValueFromArgument, NULL);

	assert_false(readArguments());
	assert_non_null(m_arguments);
}

static void test_readArguments_emptyArgumentProvided(void **state)
{
	Arguments arguments;
	(void)state;

	expect_value(UTIL_log, _logLevel, WARN);
	expect_string(UTIL_log, _message, "argument [%s] has not been provided");
	expect_string(itkc_getValueFromArgument, key, "itemId");

	will_return(mock_malloc, &arguments);
	will_return(itkc_getValueFromArgument, "");

	assert_false(readArguments());
	assert_non_null(m_arguments);
}

static void test_readArguments_argumentProvided(void **state)
{
	Arguments arguments;
	(void)state;

	expect_string(itkc_getValueFromArgument, key, "itemId");

	will_return(mock_malloc, &arguments);
	will_return(itkc_getValueFromArgument, "000017");

	assert_true(readArguments());
	assert_non_null(m_arguments);
}

static void test_logArguments(void **state)
{
	char expectedLog[256] = "\0";
	Arguments arguments;
	arguments.itemId = "000192";
	(void)state;

	m_arguments = &arguments;

	sprintf(expectedLog, "[%p]{itemId: [%s]}", m_arguments, arguments.itemId);

	expect_value(UTIL_log, _logLevel, INFO);
	expect_string(UTIL_log, _message, "[%p]{itemId: [%s]}");

	logArguments();

	assert_string_equal(expectedLog, logMessage);
}

static void test_freeArguments_notReadArguments(void **state)
{
	(void)state;
	assert_ptr_equal(NULL, m_arguments);
	freeArguments();
}

static void test_freeArguments_readArguments(void **state)
{
	(void)state;

	will_return(mock_malloc, malloc(sizeof(Arguments)));

	allocArguments();
	m_arguments->itemId = (char *)malloc(32 * sizeof(char));

	assert_ptr_not_equal(NULL, m_arguments);

	freeArguments();

	assert_ptr_equal(NULL, m_arguments);
}

static void test_getItemId_notReadArguments(void **state)
{
	(void)state;
	assert_ptr_equal(NULL, getItemId());
}

static void test_getItemId_readArguments(void **state)
{
	(void)state;

	will_return(mock_malloc, malloc(sizeof(Arguments)));

	allocArguments();
	m_allRequiredArguments = true;
	m_arguments->itemId = (char*)malloc(32 * sizeof(char));
	strcpy(m_arguments->itemId, "000123");

	assert_string_equal("000123", getItemId());

	freeArguments();
}

static int group_setUp(void **state)
{
	(void)state;
	m_memAlloc = &mock_malloc;

	return 0;
}

static int arguments_setUp(void **state)
{
	(void)state;
	m_arguments = NULL;

	return 0;
}

int main(void)
{
	const struct CMUnitTest tests_arguments[] = {
		cmocka_unit_test_setup(test_readArguments_noAllocation, arguments_setUp),
		cmocka_unit_test_setup(test_readArguments_noArgumentProvided, arguments_setUp),
		cmocka_unit_test_setup(test_readArguments_emptyArgumentProvided, arguments_setUp),
		cmocka_unit_test_setup(test_readArguments_argumentProvided, arguments_setUp),
		cmocka_unit_test(test_logArguments),
		cmocka_unit_test_setup(test_freeArguments_notReadArguments, arguments_setUp),
		cmocka_unit_test_setup(test_freeArguments_readArguments, arguments_setUp),
		cmocka_unit_test_setup(test_getItemId_notReadArguments, arguments_setUp),
		cmocka_unit_test_setup(test_getItemId_readArguments, arguments_setUp)};

	return cmocka_run_group_tests(tests_arguments, group_setUp, NULL);
}
