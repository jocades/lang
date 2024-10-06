// growable string

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char* val;
  int len;
} String;

String* string() {
  String* str = (String*)malloc(sizeof(String));
  str->len = 0;
  str->val = (char*)malloc(sizeof(char));
  str->val[0] = '\0';
  return str;
}

void freeString(String* str) {
  free(str->val);
  free(str);
}

void appendChar(String* str, char c) {
  str->len++;
  str->val = (char*)realloc(str->val, str->len + 1);
  str->val[str->len - 1] = c;
  str->val[str->len] = '\0';
}

void appendString(String* str, char* s) {
  while (*s) {
    appendChar(str, *s);
    s++;
  }
}

int main() {
  String* str = string();
  appendString(str, "Hello, ");
  appendString(str, "world!");
  printf("%s\n", str->val);
  freeString(str);
  return 0;
}
