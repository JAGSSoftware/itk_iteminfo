/**
 * @file
 * @brief
 * @since 24-01-2018
 * @author José Alberto García Sánchez
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <tcinit/tcinit.h>

#include "itkproxy.h"

int (*f_ITK_auto_login)(void) = &ITK_auto_login;
int proxy_ITK_auto_login(void)
{
    return f_ITK_auto_login();
}

int (*f_ITK_exit_module)(const logical ignoreUnsavedStuff) = &ITK_exit_module;
int proxy_ITK_exit_module(const boolean ignoreUnsavedStuff) {
    return f_ITK_exit_module(ignoreUnsavedStuff);
}

char *(*f_ITK_ask_cli_argument)(const char *) = &ITK_ask_cli_argument;
char *proxy_ITK_ask_cli_argument(const char *key)
{
    return f_ITK_ask_cli_argument(key);
}

void (*f_MEM_free)(void *ptr) = &MEM_free;
void proxy_MEM_free(void *ptr)
{
    f_MEM_free(ptr);
}

void (*f_TC_write_syslog)(const char *message, ...) = &TC_write_syslog;
void proxy_TC_write_syslog(const char *message, ...)
{
    char buffer[1024] = "\0";
    va_list argp;
    va_start(argp, message);

    vsnprintf(buffer, 1024, message, argp);
    f_TC_write_syslog(buffer);

    va_end(argp);
}

#ifdef __cplusplus
}
#endif
