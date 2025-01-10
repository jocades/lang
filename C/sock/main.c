#include "log.h"

int main() {
  char* x = "abc";
  init_logger(LOG_ERROR);
  info("hello %d", 12);
  warn("this is a warning message %s", x);
  error("this is an error message %s", x);
  return 0;
}
