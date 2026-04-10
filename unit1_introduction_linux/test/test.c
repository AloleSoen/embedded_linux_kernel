#include <stdio.h>

int main() {
    int a = 10;
    int b = 3;
    int c;

    c = a - b * 2;   // logic error: should be (a - b) * 2
    printf("Result: %d\n", c);

    return 0;
}

