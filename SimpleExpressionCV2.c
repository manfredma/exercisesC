#include <stdio.h>

int number(const char **expStr) {
    int result = **expStr - '0';
    (*expStr)++;
    return result;
}

int term(const char **expStr) {
    int result = number(expStr);
    while (**expStr == '*' || **expStr == '/' || **expStr == '%') {
        char op = **expStr;
        (*expStr)++;
        if (op == '*') {
            result *= number(expStr);
        } else if (op == '/') {
            result /= number(expStr);
        } else {
            result %= number(expStr);
        }
    }
    return result;
}

int expr(const char **expStr) {
    int result = term(expStr);
    while (**expStr == '+' || **expStr == '-') {
        char op = **expStr;
        (*expStr)++;
        if (op == '+') {
            result += term(expStr);
        } else {
            result -= term(expStr);
        }
    }
    return result;
}

int main(void) {
    char* simpleExpr = "3+3*2";
    printf("%d", expr((const char **) &simpleExpr));
    return 0;
}

