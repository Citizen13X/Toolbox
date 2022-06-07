#include <stdbool.h>
#include <stdio.h>

#if WIN32
#include <windows.h>
#else
#include <errno.h>
#endif

#include "toolbox/common.h"
#include "toolbox/log.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

#define IS_LOG_COLOR_ENABLED()    (IS_TRUE(ColorEnabled))
#define IS_VALID_LOG_LEVEL(level) ((0 <= (level)) && ((level) < MaxLogLevel))

static bool       ColorEnabled    = false;
static LogLevel_t CurrentLogLevel = LogLevelRaw;

void LogDisableColor()
{
  ColorEnabled = false;
}

void LogEnableColor()
{
#ifdef WIN32
  HANDLE OutputHandle = INVALID_HANDLE_VALUE;
  DWORD  Mode         = 0;

  OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  if (!IS_VALID_HANDLE(OutputHandle))
  {
    return;
  }

  if (IS_FALSE(GetConsoleMode(OutputHandle, &Mode)))
  {
    return;
  }
  if (IS_FALSE(SetConsoleMode(OutputHandle,
                              Mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)))
  {
    return;
  }
  if (IS_FALSE(GetConsoleMode(OutputHandle, &Mode)))
  {
    return;
  }

  if (ENABLE_VIRTUAL_TERMINAL_PROCESSING ==
      (ENABLE_VIRTUAL_TERMINAL_PROCESSING & Mode))
#endif
  {
    ColorEnabled = true;
  }
}

int32_t LogLog(
  LogLevel_t  LogLevel,
  const char* FunctionName,
  int32_t     LineNumber,
  const char* Format,
  ...)
{
  static char  output[SEGMENT_SIZE];
  static char* colors[][MaxLogLevel] = { { { "\033[1;31m" }, { "[-] " } },
                                         { { "\033[1;33m" }, { "[!] " } },
                                         { { "\033[1;32m" }, { "[+] " } },
                                         { { "\033[0m" }, { "[*] " } },
                                         { { "\033[0;37m" }, { "" } },
                                         { { "\033[1;34m" }, { "[?] " } } };

  int32_t  Length    = 0;
  uint32_t LastError = 0;
  va_list  Args      = NULL;

  if (IS_VALID_LOG_LEVEL(LogLevel) && (CurrentLogLevel < LogLevel))
  {
    goto EXIT;
  }

  if (LogLevelError == LogLevel)
  {
#if WIN32
    LastError = GetLastError();
#else
    LastError = errno;
#endif
  }

  if (IS_LOG_COLOR_ENABLED())
  {
    Length += sprintf(output, colors[LogLevel][0]);
  }
  Length += sprintf(output + Length, colors[LogLevel][1]);

  switch (LogLevel)
  {
    case LogLevelError:
    case LogLevelWarn:
      Length += sprintf(output + Length, "[%s:%i] ", FunctionName, LineNumber);
      break;

    default: break;
  }

  if (LogLevelError == LogLevel && !IS_ZERO(LastError))
  {
#if WIN32
    Length += sprintf(output + Length, "/!\\ LE 0x%08X /!\\ ", LastError);
#else
    Length += sprintf(output + Length, "/!\\ errno 0x%08X /!\\ ", LastError);
#endif
  }

  va_start(Args, Format);
  Length += vsprintf(output + Length, Format, Args);
  va_end(Args);

  if (IS_LOG_COLOR_ENABLED())
  {
    Length += sprintf(output + Length, "\033[0m");
  }
  Length += sprintf(output + Length, "\n");

  fprintf(stdout, output);

EXIT:
  return Length;
}

void LogSetLevel(LogLevel_t LogLevel)
{
  if (IS_VALID_LOG_LEVEL(LogLevel))
  {
    CurrentLogLevel = LogLevel;
  }
}
