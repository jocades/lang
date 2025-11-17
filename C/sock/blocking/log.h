#ifndef log_h
#define log_h

#define RESET "\x1B[0m"
#define GREEN "\x1B[32m"
#define ORANGE "\x1B[38;5;214m"
#define RED "\x1B[31m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"

typedef enum {
  LOG_TRACE = 1,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
} LogLevel;

void log_msg(LogLevel level, const char* fmt, ...);
void init_logger(LogLevel level);

#define trace(fmt, ...) log_msg(LOG_TRACE, fmt, ##__VA_ARGS__)
#define debug(fmt, ...) log_msg(LOG_DEBUG, fmt, ##__VA_ARGS__)
#define error(fmt, ...) log_msg(LOG_ERROR, fmt, ##__VA_ARGS__)
#define warn(fmt, ...) log_msg(LOG_WARN, fmt, ##__VA_ARGS__)
#define info(fmt, ...) log_msg(LOG_INFO, fmt, ##__VA_ARGS__)

#endif  // !log_h
