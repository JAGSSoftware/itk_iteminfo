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

#include <string.h>

#include "util.h"

// Here is included the source file under test
#include "logger.c"

static char myMessage[256] = "\0"; //<! Variable to store the logger output

/**
 * @brief Mock function
 */
static int mock_loggerFunction(const char *message)
{
	check_expected_ptr(message);

	return mock_type(int);
}

/**
 * @brief Mock function
 */
static time_t mockGetCurrentTime(time_t *_time)
{
	(void)_time;
	return (time_t)mock();
}

/*
 * Test cases
 */
// formatTime
static void test_formatTime(void **state)
{
	(void)state;

	assert_string_equal("2017-Aug-31 14:17:54", m_formatTime(1504189074));
}

// formatLogLevel
static void test_formatLogLevel_ERROR(void **state)
{
	(void)state;
	assert_string_equal("[ERROR]", m_formatLogLevel(ERROR));
}

static void test_formatLogLevel_WARN(void **state)
{
	(void)state;
	assert_string_equal("[WARN ]", m_formatLogLevel(WARN));
}

static void test_formatLogLevel_INFO(void **state)
{
	(void)state;
	assert_string_equal("[INFO ]", m_formatLogLevel(INFO));
}

static void test_formatLogLevel_DEBUG(void **state)
{
	(void)state;
	assert_string_equal("[DEBUG]", m_formatLogLevel(DEBUG));
}

static void test_formatLogLevel_TRACE(void **state)
{
	(void)state;
	assert_string_equal("[TRACE]", m_formatLogLevel(TRACE));
}

// UTIL_log
static void test_UTIL_log_TraceButMinimumIsError(void **state)
{
	(void)state;
	UTIL_log(TRACE, "Hello %s", "Jose");

	assert_string_equal("", myMessage);
}

static void test_UTIL_log_DebugButMinimumIsError(void **state)
{
	(void)state;

	UTIL_log(DEBUG, "Hello %s", "Jose");

	assert_string_equal("", myMessage);
}

static void test_UTIL_log_InfoButMinimumIsError(void **state)
{
	(void)state;

	UTIL_log(INFO, "Hello %s", "Jose");

	assert_string_equal("", myMessage);
}

static void test_UTIL_log_WarnButMinimumIsError(void **state)
{
	(void)state;

	UTIL_log(WARN, "Hello %s", "Jose");

	assert_string_equal("", myMessage);
}

static void test_UTIL_log_ErrorButMinimumIsError(void **state)
{
	char expectedMessage[] = "[ERROR] 2017-Aug-31 14:17:54: Hello Jose";
	(void)state;

	expect_string(mock_loggerFunction, message, expectedMessage);
	will_return(mockGetCurrentTime, 1504189074);
	will_return(mock_loggerFunction, strlen(expectedMessage));

	UTIL_log(ERROR, "Hello %s", "Jose");
}

static int test_UTIL_log_ErrorButMinimumIsError_setUp(void **state)
{
	(void)state;
	loggerFunction = &mock_loggerFunction;

	return 0;
}

static void test_UTIL_log_ErrorButMinimumIsError_withLineCarrier(void **state)
{
	char expectedMessage[] = "[ERROR] 2017-Aug-31 14:17:54: Hello Jose\n";
	(void)state;
	appendLineCarrier = 1;

	expect_string(mock_loggerFunction, message, expectedMessage);
	will_return(mockGetCurrentTime, 1504189074);
	will_return(mock_loggerFunction, strlen(expectedMessage));

	UTIL_log(ERROR, "Hello %s", "Jose");
}

static void test_UTIL_setLogLevel_ERROR(void **state)
{
	(void)state;
	assert_int_equal(ERROR, minimumLogLevel);

	UTIL_setLogLevel(ERROR);

	assert_int_equal(ERROR, minimumLogLevel);
}

static void test_UTIL_setLogLevel_WARN(void **state)
{
	(void)state;
	assert_int_equal(ERROR, minimumLogLevel);

	UTIL_setLogLevel(WARN);

	assert_int_equal(WARN, minimumLogLevel);
}

static void test_UTIL_setLogLevel_INFO(void **state)
{
	(void)state;
	assert_int_equal(ERROR, minimumLogLevel);

	UTIL_setLogLevel(INFO);

	assert_int_equal(INFO, minimumLogLevel);
}

static void test_UTIL_setLogLevel_DEBUG(void **state)
{
	(void)state;
	assert_int_equal(ERROR, minimumLogLevel);

	UTIL_setLogLevel(DEBUG);

	assert_int_equal(DEBUG, minimumLogLevel);
}

static void test_UTIL_setLogLevel_TRACE(void **state)
{
	(void)state;
	assert_int_equal(ERROR, minimumLogLevel);

	UTIL_setLogLevel(TRACE);

	assert_int_equal(TRACE, minimumLogLevel);
}

// UTIL_setLoggerFunction
static void test_UTIL_setLoggerFunction_NULL(void **state)
{
	(void)state;
	assert_non_null(loggerFunction);

	UTIL_setLoggerFunction(NULL);

	assert_non_null(loggerFunction);
}

static int myLoggerFunction(const char *message)
{
	(void)message;
	return 0;
}

static void test_UTIL_setLoggerFunction_notNULL(void **state)
{
	(void)state;
	assert_non_null(loggerFunction);

	will_return(mockGetCurrentTime, 12313213123);

	UTIL_setLoggerFunction(myLoggerFunction);
	UTIL_log(ERROR, "");

	assert_ptr_equal(&myLoggerFunction, loggerFunction);
}

// UTIL_setAppendLineCarrier
static void test_UTIL_setAppendLineCarrier_true(void **state)
{
	(void)state;
	assert_int_equal(0, appendLineCarrier);

	UTIL_setAppendLineCarrier(123423);

	assert_int_equal(1, appendLineCarrier);
}

static void test_UTIL_setAppendLineCarrier_false(void **state)
{
	(void)state;
	assert_int_equal(0, appendLineCarrier);

	UTIL_setAppendLineCarrier(0);

	assert_int_equal(0, appendLineCarrier);
}

static int group_setup(void **state)
{
	(void)state;
	m_getCurrentTime = &mockGetCurrentTime;

	return 0;
}

static int UTIL_setLogLevel_setup(void **state)
{
	(void)state;
	minimumLogLevel = ERROR;
	return 0;
}

static int UTIL_setLoggerFunction_setup(void **state)
{
	(void)state;
	loggerFunction = &puts;
	return 0;
}

static int UTIL_setAppendLineCarrier_setup(void **state)
{
	(void)state;
	appendLineCarrier = 0;
	return 0;
}

int main(void)
{
	const struct CMUnitTest tests_logger[] = {
		// formatTime
		cmocka_unit_test(test_formatTime),
		// formatLogLevel
		cmocka_unit_test(test_formatLogLevel_ERROR),
		cmocka_unit_test(test_formatLogLevel_WARN),
		cmocka_unit_test(test_formatLogLevel_INFO),
		cmocka_unit_test(test_formatLogLevel_DEBUG),
		cmocka_unit_test(test_formatLogLevel_TRACE),
		// UTIL_log
		cmocka_unit_test(test_UTIL_log_TraceButMinimumIsError),
		cmocka_unit_test(test_UTIL_log_DebugButMinimumIsError),
		cmocka_unit_test(test_UTIL_log_InfoButMinimumIsError),
		cmocka_unit_test(test_UTIL_log_WarnButMinimumIsError),
		cmocka_unit_test_setup(test_UTIL_log_ErrorButMinimumIsError, test_UTIL_log_ErrorButMinimumIsError_setUp),
		cmocka_unit_test_setup(test_UTIL_log_ErrorButMinimumIsError_withLineCarrier, test_UTIL_log_ErrorButMinimumIsError_setUp),
		// UTIL_setLogLevel
		cmocka_unit_test_setup(test_UTIL_setLogLevel_ERROR, UTIL_setLogLevel_setup),
		cmocka_unit_test_setup(test_UTIL_setLogLevel_WARN, UTIL_setLogLevel_setup),
		cmocka_unit_test_setup(test_UTIL_setLogLevel_INFO, UTIL_setLogLevel_setup),
		cmocka_unit_test_setup(test_UTIL_setLogLevel_DEBUG, UTIL_setLogLevel_setup),
		cmocka_unit_test_setup(test_UTIL_setLogLevel_TRACE, UTIL_setLogLevel_setup),
		// UTIL_setLoggerFunction
		cmocka_unit_test_setup(test_UTIL_setLoggerFunction_NULL, UTIL_setLoggerFunction_setup),
		cmocka_unit_test_setup(test_UTIL_setLoggerFunction_notNULL, UTIL_setLoggerFunction_setup),
		// UTIL_setAppendLineCarrier
		cmocka_unit_test_setup(test_UTIL_setAppendLineCarrier_true, UTIL_setAppendLineCarrier_setup),
		cmocka_unit_test_setup(test_UTIL_setAppendLineCarrier_false, UTIL_setAppendLineCarrier_setup),
	};

	return cmocka_run_group_tests(tests_logger, group_setup, NULL);
}
