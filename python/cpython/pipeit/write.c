#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i <= atoi(argv[1]); i++) {
        printf("%d ", i);
    }

    return 0;
}
