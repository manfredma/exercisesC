#include <stdio.h>

int number(const char *expStr) {
    return *expStr - '0';
}

int expr(const char *expStr) {
    int result = number(expStr++);
    while (*expStr == '+' || *expStr == '-') {
        char op = *expStr;
        expStr++;
        if (op == '+') {
            result += number(expStr++);
        } else {
            result -= number(expStr++);
        }
    }
    return result;
}

int main(void) {
    printf("%d", expr("3+3-2"));
    return 0;
}

