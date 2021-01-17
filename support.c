#include <stdio.h>

extern int count2;

void write_extern(void) {
    printf("count is %d\n", count2);
}