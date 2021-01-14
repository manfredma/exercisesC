/*
 C 共用体
 共用体是一种特殊的数据类型，允许您在相同的内存位置存储不同的数据类型。您可以定义一个带有多成员的共用体，但是任何时候只能有一个成员带有值。
 共用体提供了一种使用相同的内存位置的有效方式。
 定义共用体
 为了定义共用体，您必须使用 union 语句，方式与定义结构类似。union 语句定义了一个新的数据类型，带有多个成员。union 语句的格式如下：
 union [union tag]
 {
    member definition;
    member definition;
    ...
    member definition;
 } [one or more union variables];

 */
#include <stdio.h>
#include <string.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    printf("Memory size occupied by data : %lu\n", sizeof(data));

    data.i = 10;
    data.f = 220.5F;
    strcpy(data.str, "C Programming");

    printf("data.i : %d\n", data.i);
    printf("data.f : %f\n", data.f);
    printf("data.str : %s\n", data.str);

    data.i = 10;
    printf("data.i : %d\n", data.i);

    data.f = 220.5F;
    printf("data.f : %f\n", data.f);

    strcpy(data.str, "C Programming");
    printf("data.str : %s\n", data.str);

    return 0;
}