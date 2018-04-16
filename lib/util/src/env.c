/**
 * @file
 * @brief
 * @since 24-08-2017
 * @author José Alberto García Sánchez
 */

#include <stdlib.h>
#include "types.h"
#include "env.h"
#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

static char *(*m_getEnvironmentVariableValue)(const char *_varName) = &getenv;

boolean ENV_isSetEnvironmentVariable(const char *variableName)
{
	char *buffer;
	boolean isSet = false;

	buffer = m_getEnvironmentVariableValue(variableName);

	isSet = (buffer != NULL);
	if (isSet)
	{
		UTIL_log(DEBUG, "Variable [%s] has the value [%s]", variableName, buffer);
	}
	else
	{
		UTIL_log(WARN, "Variable [%s] has not been set", variableName);
	}

	return isSet;
}

#ifdef __cplusplus
}
#endif
