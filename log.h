#ifndef __TOOLBOX_LOG_H__
#define __TOOLBOX_LOG_H__

#include <stdint.h>

#define LOG_ERROR(...) \
  LogLog(LogLevelError, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) \
  LogLog(LogLevelWarn, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_SUCCESS(...) \
  LogLog(LogLevelSuccess, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) \
  LogLog(LogLevelInfo, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_RAW(...) \
  LogLog(LogLevelRaw, __FUNCTION__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) \
  LogLog(LogLevelDebug, __FUNCTION__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum LogLevel
{
  LogLevelError,
  LogLevelWarn,
  LogLevelSuccess,
  LogLevelInfo,
  LogLevelRaw,
  LogLevelDebug,

  MaxLogLevel
} LogLevel_t;

void LogDisableColor();

void LogEnableColor();

int32_t LogLog(
  LogLevel_t  LogLevel,
  const char* FunctionName,
  int32_t     LineNumber,
  const char* Format,
  ...);

void LogSetLevel(
  LogLevel_t LogLevel);

#ifdef __cplusplus
}
#endif

#endif // __TOOLBOX_LOG_H__
