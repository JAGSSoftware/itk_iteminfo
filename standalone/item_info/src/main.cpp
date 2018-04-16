/**
 * @file
 * @brief
 * @since 22.08.2017
 * @author José Alberto García Sánchez
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// This include is required to link the executable with TC libs
#include <tc/tc.h>

#include "itkproxy.h"
#include "itkproxy_pom.h"

#include "types.h"
#include "logger.h"
#include "env.h"

#include "itemInfo.h"
#include "arguments.h"

/**
 * @ingroup item_info
 * @{
 */

int myLogger(const char *message)
{
	printf("%s", message);
	proxy_TC_write_syslog(message);

	return 0;
}

/**
 * @brief
 */
static void configureLogger()
{
	UTIL_setLogLevel(INFO);
	UTIL_setLoggerFunction(&myLogger);
	UTIL_setAppendLineCarrier(true);
}

/**
 * @brief
 * @return
 */
static boolean areRequiredEnvironmentVariablesSet()
{
	boolean _isTcDbConnectSet = false;
	boolean _isTcRootSet = false;
	boolean _isTcDataSet = false;

	UTIL_log(DEBUG, "Checking the required environment variables");

	_isTcDbConnectSet = ENV_isSetEnvironmentVariable("TC_DB_CONNECT");
	_isTcRootSet = ENV_isSetEnvironmentVariable("TC_ROOT");
	_isTcDataSet = ENV_isSetEnvironmentVariable("TC_DATA");

	return _isTcDbConnectSet && _isTcRootSet && _isTcDataSet;
}

/**
 * @brief Entry point of the utility
 * @param[in] argc Number of arguments for the utility
 * @param[in] argv Arguments for the utility
 * @return @code 0 if success, any other value otherwise
 */
int ITK_user_main(int argc, char **argv)
{
	ItemInfo *_itemInfo;
	(void)argc;
	(void)argv;

	configureLogger();

	if (!areRequiredEnvironmentVariablesSet())
	{
		UTIL_log(INFO, "Missing required environment variables");
		return -1;
	}

	if (!readArguments())
	{
		freeArguments();
		UTIL_log(ERROR, "Error reading the arguments.");
		proxy_ITK_exit_module(false);
		return -1;
	}

	if (proxy_ITK_auto_login() != ITK_ok)
	{
		UTIL_log(WARN, "Error when auto logging in.");
		proxy_ITK_exit_module(false);
		freeArguments();
		return -1;
	}

	proxy_POM_init_module();

	_itemInfo = ITEM_INFO_get(getItemId());
	if (_itemInfo != NULL)
	{
		ITEM_INFO_write(_itemInfo);
		ITEM_INFO_free(&_itemInfo);
	}

	freeArguments();

	proxy_ITK_exit_module(false);

	return 0;
}

/**
 * @}
 */
