#include <stdio.h>

/* Multi-line comment should be removed. */
#define VALUE 10

int main() {
    int count    =    VALUE;   // Initialize count
    char slash = '/';
    char star = '*';
    printf("Hello // this is inside a string\n");
    printf("/* also not a comment */\n");

    if (count > 0) {
        printf("Count = %d\n", count);
    }
    return 0;
}
