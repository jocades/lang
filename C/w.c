#include <stdio.h>

void print(char *s) {
    while (*s != '\0') {
        printf("%c", *s);
        s++;
    }
    printf("\n");
}


int main() {
    char *s = "hello";

    print(s);
    return 0;
}
