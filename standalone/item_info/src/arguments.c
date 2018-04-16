/**
 * @file
 * @brief
 * @since 28-08-2017
 * @author José Alberto García Sánchez
 */

#include <stdlib.h>
#include <string.h>

#include "logger.h"
#include "types.h"
#include "itkconnector.h"

/**
 * @addtogroup item_info
 * @{
 */

typedef struct Arguments
{
	char *itemId; //<! id of the item to be sought
} Arguments;

/**
 * @brief wrap function to allocate memory
 */
static void *(*m_memAlloc)(size_t _Size) = &malloc;

Arguments *m_arguments = NULL;
boolean m_allRequiredArguments = false;

/**
 * @brief
 * @return
 */
static boolean isArgumentsRead(void)
{
	return m_arguments != NULL && m_allRequiredArguments;
}

/**
 * @brief
 */
static void allocArguments(void)
{
	if (m_arguments == NULL)
	{
		m_arguments = m_memAlloc(sizeof(Arguments));
	}
}

boolean readArguments(void)
{
	allocArguments();
	if (m_arguments == NULL)
	{
		UTIL_log(ERROR, "Error when creating Arguments.");
		return false;
	}

	m_arguments->itemId = itkc_getValueFromArgument("itemId");
	if (m_arguments->itemId == NULL || strcmp("", m_arguments->itemId) == 0)
	{
		UTIL_log(WARN, "argument [%s] has not been provided", "itemId");
	}
	else
	{
		m_allRequiredArguments = true;
	}

	return isArgumentsRead();
}

void freeArguments(void)
{
	if (m_arguments != NULL)
	{
		free(m_arguments->itemId);
		free(m_arguments);
		m_arguments = NULL;
	}
}

void logArguments(void)
{
	if (m_arguments != NULL)
	{
		UTIL_log(INFO, "[%p]{itemId: [%s]}", m_arguments, m_arguments->itemId);
	}
}

const char *getItemId(void)
{
	if (isArgumentsRead())
	{
		return m_arguments->itemId;
	}
	return NULL;
}

/**
 * @}
 */
