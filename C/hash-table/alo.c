#include <stdio.h>

typedef struct {
  const char* name;
  int age;
} User;

User new_user(const char* name, int age) {
  User user = {name, age};
  return user;
}

int main() {
  User user = new_user("john", 10);
  printf("%s %d\n", user.name, user.age);

  char* what = "hello";
  char f1 = *what;
  char f2 = what[0];

  printf("%c %c\n", f1, f2);

  char s1 = what[2];
  char s2 = *(what + sizeof(char) * 2);
  printf("%c %c\n", s1, s2);

  return 0;
}
