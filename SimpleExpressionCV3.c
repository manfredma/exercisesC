#include <stdio.h>

int number(const char **expStr);
int term(const char **expStr);
int factor(const char **expStr);
int expr(const char **expStr);



int number(const char **expStr) {
    int result = **expStr - '0';
    (*expStr)++;
    return result;
}

int factor(const char **expStr) {
    if (**expStr == '(') {
        (*expStr)++;
        int result = expr(expStr);
        // 跳过后括号，没有检查括号是否匹配
        (*expStr)++;
        return result;
    } else {
        return number(expStr);
    }
}

int term(const char **expStr) {
    int result = factor(expStr);
    while (**expStr == '*' || **expStr == '/' || **expStr == '%') {
        char op = **expStr;
        (*expStr)++;
        if (op == '*') {
            result *= factor(expStr);
        } else if (op == '/') {
            result /= factor(expStr);
        } else {
            result %= factor(expStr);
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
    char* simpleExpr = "(3+3)*2/(3+1)";
    printf("%d", expr((const char **) &simpleExpr));
    return 0;
}

