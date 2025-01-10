#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static LogLevel current_log_level = -1;

const char* level_to_str(LogLevel level) {
  switch (level) {
    case LOG_TRACE: return "TRACE";
    case LOG_DEBUG: return "DEBUG";
    case LOG_INFO: return "INFO";
    case LOG_WARN: return "WARN";
    case LOG_ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}

LogLevel str_to_level(const char* level_str) {
  if (strcmp(level_str, "TRACE") == 0) return LOG_TRACE;
  if (strcmp(level_str, "DEBUG") == 0) return LOG_DEBUG;
  if (strcmp(level_str, "INFO") == 0) return LOG_INFO;
  if (strcmp(level_str, "WARN") == 0) return LOG_WARN;
  if (strcmp(level_str, "ERROR") == 0) return LOG_ERROR;
  return LOG_INFO;
}

LogLevel get_env_log_level() {
  const char* level_str = getenv("LOG_LEVEL");
  if (level_str == NULL) return LOG_INFO;
  return str_to_level(level_str);
}

void datetime() {
  time_t now = time(NULL);
  char str[20];
  strftime(str, sizeof(str), "%Y-%m-%dT%H:%M:%S", localtime(&now));
  printf("[%s] ", str);
}

void log_msg(LogLevel level, const char* fmt, ...) {
  // Don't print logs below the set level
  if (level < current_log_level) return;

  datetime();
  switch (level) {
    case LOG_TRACE: printf(MAGENTA);
    case LOG_DEBUG: printf(BLUE);
    case LOG_ERROR: printf(RED); break;
    case LOG_WARN: printf(ORANGE); break;
    case LOG_INFO: printf(GREEN); break;
  }
  printf(" %s" RESET " ", level_to_str(level));

  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  puts("");
}

// Initialize the logger, optionally passing a log level
void init_logger(LogLevel level) {
  if (level <= 0) {
    current_log_level = get_env_log_level();
  } else {
    current_log_level = level;
  }
}
