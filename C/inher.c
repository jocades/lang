#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OBJ_STRING,
  OBJ_FUNCTION
} ObjType;

typedef struct Obj {
  ObjType type;
  struct Obj* next;
} Obj;

typedef struct {
  Obj obj;
  char* ptr;
  size_t len;
} ObjString;

#define AS_STRING(obj) ((ObjString*)obj)

typedef struct {
  Obj* objects;
} VM;

VM vm;

void initVM() {
  vm.objects = NULL;
}

ObjString* allocateString(const char* chars, size_t len) {
  char* heap_chars = malloc(sizeof(char) * len + 1);
  memcpy(heap_chars, chars, len);
  heap_chars[len] = '\0';

  ObjString* s = malloc(sizeof(ObjString));
  s->ptr = heap_chars;
  s->len = len;

  Obj* o = (Obj*)s;
  o->type = OBJ_STRING;
  o->next = vm.objects;
  vm.objects = o;

  return s;
}

typedef enum {
  VAL_NUMBER,
  VAL_OBJ,
} ValueType;

typedef struct {
  ValueType type;
  union {
    double number;
    Obj* obj;
  } as;
} Value;

#define MK_DA(Name, T) \
  typedef struct {     \
    T* ptr;            \
    size_t len;        \
    size_t cap;        \
  } Name

#define DA_INIT(da)   \
  do {                \
    (da)->ptr = NULL; \
    (da)->len = 0;    \
    (da)->cap = 0;    \
  } while (0)

#define DA_PUSH(da, v)                               \
  do {                                               \
    if ((da)->len >= (da)->cap) {                    \
      (da)->cap = (da)->cap < 8 ? 8 : (da)->cap * 2; \
      (da)->ptr = realloc((da)->ptr, (da)->cap);     \
      if ((da)->ptr == NULL) {                       \
        fprintf(stderr, "ALLOC FAILED");             \
        exit(1);                                     \
      }                                              \
    }                                                \
    (da)->ptr[(da)->len++] = v;                      \
  } while (0)

#define DA_POP(da) (((da)->ptr)[--((da)->len)])

MK_DA(ValueArray, int);

int main() {
  allocateString("first", 5);
  allocateString("second", 6);

  Obj* current = vm.objects;
  while (current != NULL) {
    printf("%s\n", ((ObjString*)current)->ptr);
    current = current->next;
  }

  ValueArray values = {0};

  /* DA_INIT(&values); */
  DA_PUSH(&values, 1);
  DA_PUSH(&values, 2);
  DA_PUSH(&values, 3);

  for (int i = 0; i < values.len; i++) {
    printf("%d\n", values.ptr[i]);
  }

  int x = DA_POP(&values);
  int y = DA_POP(&values);
  int z = DA_POP(&values);
  printf("%d, %d, %d, len = %zu\n", x, y, z, values.len);

  return 0;
}
