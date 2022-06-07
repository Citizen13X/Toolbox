#include <stdint.h>
#include <stdlib.h>

#if WIN32
#include <windows.h>
#else
#include <errno.h>
#endif

#include "toolbox/log.h"

#define ERROR_CODE 0x0BADC0DE

static char __ColoredTestString__[] = "Hello colored world!";
static char __TestString__[]        = "Hello world!";

int32_t main()
{
  LogSetLevel(LogLevelDebug);

#if WIN32
  SetLastError(ERROR_CODE);
#else
  _set_errno(ERROR_CODE);
#endif

  LOG_ERROR("%s", __TestString__);
  LOG_WARN("%s", __TestString__);
  LOG_SUCCESS("%s", __TestString__);
  LOG_INFO("%s", __TestString__);
  LOG_RAW("%s", __TestString__);
  LOG_DEBUG("%s", __TestString__);

  LogEnableColor();

#if WIN32
  SetLastError(ERROR_CODE);
#else
  _set_errno(ERROR_CODE);
#endif

  LOG_ERROR("%s", __ColoredTestString__);
  LOG_WARN("%s", __ColoredTestString__);
  LOG_SUCCESS("%s", __ColoredTestString__);
  LOG_INFO("%s", __ColoredTestString__);
  LOG_RAW("%s", __ColoredTestString__);
  LOG_DEBUG("%s", __ColoredTestString__);

  return EXIT_SUCCESS;
}
