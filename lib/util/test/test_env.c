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

#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "util.h"

// Here it is included the source file under test
#include "env.c"

static char temporary_buffer[256]; //<! Variable to store the logger output

/**
 * @brief mock function
 * @see UTIL_log defined in logger.h
 */
void UTIL_log(const LogLevel logLevel, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsprintf(temporary_buffer, fmt, args);
	(void)fmt;

	check_expected(logLevel);
	check_expected_ptr(temporary_buffer);
	check_expected_ptr(fmt);

	va_end(args);
}

/**
 * @brief mock function of \c getenv
 * @see getenv() in stdlib.h
 */
char *myGetEnv(const char *_varName)
{
	(void)_varName;
	return (char *)mock();
}

static void test_ENV_isSetEnvironmentVariableSet(void **state)
{
	char *expectedString = "Here the value";
	(void)state;

	expect_value(UTIL_log, logLevel, DEBUG);
	expect_string(UTIL_log, temporary_buffer, "Variable [JAVA_HOME] has the value [Here the value]");
	expect_string(UTIL_log, fmt, "Variable [%s] has the value [%s]");

	will_return(myGetEnv, expectedString);

	assert_true(ENV_isSetEnvironmentVariable("JAVA_HOME"));
}

static void test_ENV_isSetEnvironmentVariableNotSet(void **state)
{
	(void)state;

	expect_value(UTIL_log, logLevel, WARN);
	expect_string(UTIL_log, temporary_buffer, "Variable [BLA_BLA_ENVIRONMENT] has not been set");
	expect_string(UTIL_log, fmt, "Variable [%s] has not been set");

	will_return(myGetEnv, NULL);

	assert_false(ENV_isSetEnvironmentVariable("BLA_BLA_ENVIRONMENT"));
}

static int group_setUp(void **state)
{
	(void)state;
	m_getEnvironmentVariableValue = &myGetEnv;

	return 0;
}

int main(void)
{
	const struct CMUnitTest tests_environment[] = {
		cmocka_unit_test(test_ENV_isSetEnvironmentVariableSet),
		cmocka_unit_test(test_ENV_isSetEnvironmentVariableNotSet)};

	return cmocka_run_group_tests(tests_environment, group_setUp, NULL);
}
