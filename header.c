#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
    puts(test());
    return 0;
}

char *test() {
    char *x = (char *) malloc(10 * sizeof(char));
    for (int i = 0; i < 10; i++) {
        *(x + i) = (char) (i + 'a');
    }
    *(x + 10) = '\0';
    return x;
}