#include <stdio.h>

// From C to shared object (to be used as a library)
// gcc -o libmy_math.so -fpic -shared my_math.c
int my_add(int a, int b) {
    return a + b;
}

int my_sub(int a, int b) {
    return a - b;
}
