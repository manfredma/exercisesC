/*
 * 每一个变量都有一个内存位置，每一个内存位置都定义了可使用 & 运算符访问的地址，它表示了在内存中的一个地址。
 */
// 什么是指针？
// 指针是一个变量，其值为另一个变量的地址，即，内存位置的直接地址。就像其他变量或常量一样，您必须在使用指针存储其他变量地址之前，对其进行声明。
// 指针变量声明的一般形式为：type *var-name;
// 在这里，type 是指针的基类型，它必须是一个有效的 C 数据类型，var-name 是指针变量的名称。用来声明指针的星号 * 与乘法中使用的星号是相同的。
// 但是，在这个语句中，星号是用来指定一个变量是指针。以下是有效的指针声明：
// int    *ip;    /* 一个整型的指针 */
// double *dp;    /* 一个 double 型的指针 */
// float  *fp;    /* 一个浮点型的指针 */
// char   *ch;    /* 一个字符型的指针 */
// 所有实际数据类型，不管是整型、浮点型、字符型，还是其他的数据类型，对应指针的值的类型都是一样的，都是一个代表内存地址的长的十六进制数。
// 不同数据类型的指针之间唯一的不同是，指针所指向的变量或常量的数据类型不同。
#include <stdio.h>

enum x {a, b};

int main() {

    /* 基本示例 */
    int var = 10;
    int *ip;              // 定义指针变量
    ip = &var;


    printf("var 变量的地址: %p\n", &var);

    /* 在指针变量中存储的地址 */
    printf("ip 变量存储的地址: %p\n", ip);

    /* 使用指针访问值 */
    printf("*ip 变量的值: %d\n", *ip);

    /* NULL 指针 */
    int *ptr = NULL;

    printf("ptr 的地址是 %p\n", ptr);

    enum x x= a;
    x++;
    printf("x=%d", x);

    return 0;
}

