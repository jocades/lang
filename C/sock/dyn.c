#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char* name;
  int age;
} User;

typedef struct {
  User** ptr;
  size_t len;
  size_t cap;
} Users;

void append(Users* users, User* user) {
  if (users->cap < users->len + 1) {
    size_t cap = users->cap;
    users->cap = cap < 8 ? 8 : cap * 2;
    users->ptr = realloc(users->ptr, users->cap * sizeof(*users->ptr));
  }
  users->ptr[users->len] = user;
  users->len++;
}

int main() {
  Users users = {NULL, 0, 0};

  char name[6];
  for (int i = 0; i < 5; i++) {
    User* user = malloc(sizeof(User));
    sprintf(name, "user%d", i);
    user->name = strdup(name);
    user->age = i + 1;
    append(&users, user);
  }

  for (size_t i = 0; i < users.len; i++) {
    User* user = users.ptr[i];
    printf("%s %d\n", user->name, user->age);
  }

  return 0;
}
