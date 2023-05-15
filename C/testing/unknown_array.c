#include <stdio.h>
#include <stdlib.h>

// Create an array of unknown size or datatype

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    void* ptr = malloc(size * sizeof(int)); // allocate memory for the array

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int* arr = ptr; // cast the void pointer to an integer pointer

    for (int i = 0; i < size; i++) {
        printf("Enter the value for index %d: ", i);
        scanf("%d", &arr[i]);
    }

    printf("Array values: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    free(ptr); // deallocate memory for the array
    return 0;
}

