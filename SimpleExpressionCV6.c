#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>

enum {
    SLM_EXPRESSION_ERROR_NONE = 0,
    SLM_EXPRESSION_ERROR_EXPECT_DIGIT,
    SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO,
    SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO,
    SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS,
    SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS,
    SLM_EXPRESSION_ERROR_EXPECT_ID,
    SLM_EXPRESSION_ERROR_EXPECT_COMMA,
    SLM_EXPRESSION_ERROR_UNKNOW_FUNCTION,
    SLM_EXPRESSION_ERROR_EXPECT_END,
    SLM_EXPRESSION_ERROR_UNKNOW_TOKEN,
};

int slm_eval(const char *expStr, int *errType);

enum {
    SLM_EXPRESSION_TOKEN_UNKNOWN = 0,
    SLM_EXPRESSION_TOKEN_DIGITS,
    SLM_EXPRESSION_TOKEN_ID,
    SLM_EXPRESSION_TOKEN_ADD,
    SLM_EXPRESSION_TOKEN_SUB_OR_MINUS,
    SLM_EXPRESSION_TOKEN_MUL,
    SLM_EXPRESSION_TOKEN_DIV,
    SLM_EXPRESSION_TOKEN_MOD,
    SLM_EXPRESSION_TOKEN_OPEN,
    SLM_EXPRESSION_TOKEN_CLOSE,
    SLM_EXPRESSION_TOKEN_COMMA,
    SLM_EXPRESSION_TOKEN_END
};

typedef struct {
    int type;
    int value;
    char *name;
} slm_token;

typedef struct {
    const char *expStr;
    slm_token token;
    int errType;
} slm_expr;

int expr(slm_expr *e);

#define TRY(func) func; if (e->errType) return 0;
#define THROW(error) e->errType = error; return 0;

void next(slm_expr *e) {
    if (e->token.name) {
        free(e->token.name);
        e->token.name = NULL;
    }
    while (isspace(*e->expStr)) {
        (e->expStr)++;
    }
    if (*e->expStr == 0) {
        e->token.type = SLM_EXPRESSION_TOKEN_END;
    } else if (isdigit(*e->expStr)) {
        e->token.type = SLM_EXPRESSION_TOKEN_DIGITS;
        e->token.value = *e->expStr - '0';
        (e->expStr)++;
        while (isdigit(*e->expStr)) {
            e->token.value = e->token.value * 10 + (*e->expStr - '0');
            (e->expStr)++;
        }
    } else if (isalpha(*e->expStr)) {
        e->token.type = SLM_EXPRESSION_TOKEN_ID;
        const char *start = e->expStr;
        do {
            (e->expStr)++;
        } while (isalpha(*e->expStr) || isdigit(*e->expStr));
        size_t length = e->expStr - start;
        char *name = calloc(length + 1, sizeof(char));
        strncpy(name, start, length);
        name[length] = '\0';
        e->token.name = name;
    } else {
        switch (*e->expStr) {
            case '+':
                e->token.type = SLM_EXPRESSION_TOKEN_ADD;
                (e->expStr)++;
                break;
            case '-':
                e->token.type = SLM_EXPRESSION_TOKEN_SUB_OR_MINUS;
                (e->expStr)++;
                break;
            case '*':
                e->token.type = SLM_EXPRESSION_TOKEN_MUL;
                (e->expStr)++;
                break;
            case '/':
                e->token.type = SLM_EXPRESSION_TOKEN_DIV;
                (e->expStr)++;
                break;
            case '%':
                e->token.type = SLM_EXPRESSION_TOKEN_MOD;
                (e->expStr)++;
                break;
            case '(':
                e->token.type = SLM_EXPRESSION_TOKEN_OPEN;
                (e->expStr)++;
                break;
            case ')':
                e->token.type = SLM_EXPRESSION_TOKEN_CLOSE;
                (e->expStr)++;
                break;
            case ',':
                e->token.type = SLM_EXPRESSION_TOKEN_COMMA;
                (e->expStr)++;
                break;
            default:
                e->token.type = SLM_EXPRESSION_TOKEN_UNKNOWN;
                e->errType = SLM_EXPRESSION_ERROR_UNKNOW_TOKEN;
                break;
        }
    }
}

int number(slm_expr *e) {
    /*
     number = '-' digits
            | digits
     */
    int hasMinus = 0;
    if (e->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        TRY(next(e));
        hasMinus = 1;
    }
    if (e->token.type != SLM_EXPRESSION_TOKEN_DIGITS) {
        THROW(SLM_EXPRESSION_ERROR_EXPECT_DIGIT);
    }
    int result = e->token.value;
    TRY(next(e));
    if (hasMinus) {
        result *= -1;
    }
    return result;
}

int func(slm_expr *e) {
    /*
     func  = func1
           | func2
     func1 = id '(' expr ')'
     func2 = id '(' expr ',' expr ')'
     */
    if (e->token.type != SLM_EXPRESSION_TOKEN_ID || !e->token.name) {
        THROW(SLM_EXPRESSION_ERROR_EXPECT_ID);
    }
    int result;
    if (strcmp(e->token.name, "max") == 0) {
        TRY(next(e));
        // '('
        if (e->token.type != SLM_EXPRESSION_TOKEN_OPEN) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS);
        }
        TRY(next(e));
        // arg1
        int arg1 = TRY(expr(e));
        // ','
        if (e->token.type != SLM_EXPRESSION_TOKEN_COMMA) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_COMMA);
        }
        TRY(next(e));
        // arg2
        int arg2 = TRY(expr(e));
        // ')'
        if (e->token.type != SLM_EXPRESSION_TOKEN_CLOSE) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS);
        }
        TRY(next(e));
        // result
        result = arg1 >= arg2 ? arg1 : arg2;
    } else if (strcmp(e->token.name, "min") == 0) {
        TRY(next(e));
        // '('
        if (e->token.type != SLM_EXPRESSION_TOKEN_OPEN) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS);
        }
        TRY(next(e));
        // arg1
        int arg1 = TRY(expr(e));
        // ','
        if (e->token.type != SLM_EXPRESSION_TOKEN_COMMA) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_COMMA);
        }
        TRY(next(e));
        // arg2
        int arg2 = TRY(expr(e));
        // ')'
        if (e->token.type != SLM_EXPRESSION_TOKEN_CLOSE) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS);
        }
        TRY(next(e));
        // result
        result = arg1 <= arg2 ? arg1 : arg2;
    } else if (strcmp(e->token.name, "abs") == 0) {
        TRY(next(e));
        // '('
        if (e->token.type != SLM_EXPRESSION_TOKEN_OPEN) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS);
        }
        TRY(next(e));
        // arg1
        result = TRY(expr(e));
        // ')'
        if (e->token.type != SLM_EXPRESSION_TOKEN_CLOSE) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS);
        }
        TRY(next(e));
        // result
        result = abs(result);
    } else {
        THROW(SLM_EXPRESSION_ERROR_UNKNOW_FUNCTION);
    }
    return result;
}

int factor(slm_expr *e) {
    /*
     factor = number
            | func
            | '(' expr ')'
     */
    int result;
    if (e->token.type == SLM_EXPRESSION_TOKEN_OPEN) {
        TRY(next(e));
        result = TRY(expr(e));
        if (e->token.type != SLM_EXPRESSION_TOKEN_CLOSE) {
            THROW(SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS);
        }
        TRY(next(e));
    } else if (e->token.type == SLM_EXPRESSION_TOKEN_ID) {
        result = TRY(func(e));
    } else {
        result = TRY(number(e));
    }
    return result;
}

int term(slm_expr *e) {
    /*
     term  = factor term1
     term1 = '*' factor term1
           | '/' factor term1
           | '%' factor term1
           | null
     */
    int result = TRY(factor(e));
    while (e->token.type == SLM_EXPRESSION_TOKEN_MUL
           || e->token.type == SLM_EXPRESSION_TOKEN_DIV
           || e->token.type == SLM_EXPRESSION_TOKEN_MOD) {
        int op = e->token.type;
        TRY(next(e));
        int f = TRY(factor(e));
        if (op == SLM_EXPRESSION_TOKEN_MUL) {
            result *= f;
        } else if (op == SLM_EXPRESSION_TOKEN_DIV) {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO);
            }
            result /= f;
        } else {
            if (f == 0) {
                THROW(SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO);
            }
            result %= f;
        }
    }
    return result;
}

int expr(slm_expr *e) {
    /*
     expr  = term expr1
     expr1 = '+' term expr1
           | '-' term expr1
           | null
     */
    int result = TRY(term(e));
    while (e->token.type == SLM_EXPRESSION_TOKEN_ADD || e->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        int op = e->token.type;
        TRY(next(e))
        int t = TRY(term(e));
        if (op == SLM_EXPRESSION_TOKEN_ADD) {
            result += t;
        } else {
            result -= t;
        }
    }
    return result;
}

int slm_eval(const char *expStr, int *errType) {
    slm_expr e;
    e.expStr = expStr;
    e.errType = SLM_EXPRESSION_ERROR_NONE;
    e.token.name = NULL;
    int result = 0;
    next(&e);
    if (e.errType == 0) {
        result = expr(&e);
        if (e.errType == 0 && e.token.type != SLM_EXPRESSION_TOKEN_END) {
            e.errType = SLM_EXPRESSION_ERROR_EXPECT_END;
            result = 0;
        }
    }
    if (e.token.name) {
        free(e.token.name);
        e.token.name = NULL;
    }
    if (errType) {
        *errType = e.errType;
    }
    return result;
}

void test(const char *expStr) {
    int errType;
    int result = slm_eval(expStr, &errType);
    switch (errType) {
        case SLM_EXPRESSION_ERROR_NONE:
            printf("%s = %d\n", expStr, result);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_DIGIT:
            printf("%s: error - expect digit\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_DIVISION_BY_ZERO:
            printf("%s: error - division by zero\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_REMAINDER_BY_ZERO:
            printf("%s: error - remainder by zero\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_OPEN_PARENTHESIS:
            printf("%s: error - expect '('\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_CLOSE_PARENTHESIS:
            printf("%s: error - expect ')'\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_ID:
            printf("%s: error - expect ID\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_COMMA:
            printf("%s: error - expect comma\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_UNKNOW_FUNCTION:
            printf("%s: error - unknown function\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_EXPECT_END:
            printf("%s: error - expect end\n", expStr);
            break;
        case SLM_EXPRESSION_ERROR_UNKNOW_TOKEN:
            printf("%s: error - unknown token\n", expStr);
            break;
        default:
            printf("%s: unknown error\n", expStr);
            break;
    }
}

int main(int argc, const char *argv[]) {

    test("1    +    2");
    test("3-2+10");
    test("2 *\t\t3");
    test("3+4/2-10");
    test("1 * 2 + 3 % 2");
    test("2*2*2-30");
    test("(2 + 4) / 3");
    test("(10+2)*(20+2)");
    test("(1 + 3 * 2) % 3");
    test("10+)");
    test("1 / 0");
    test("10%0");
    test("(2 + 3 * 4");
    test("10+2)");
    test("2 * -3");
    test("10--12");
    test("1?");
    test("max(1, 2) * 2");
    test("abs(-2) * 2");
    test("max(2) * 2");
    test("fun1(2) * 2");
    return 0;
}