/*
 在 C 语言中，字符串实际上是使用 null 字符 \0 终止的一维字符数组。因此，一个以 null 结尾的字符串，包含了组成字符串的字符。
 */
#include <stdio.h>
#include <string.h>

int main() {
    char str1[14] = "runoob";
    char str2[14] = "google";
    char str3[14];

    printf("str1=%s, str2=%s\n", str1, str2);

    /* 复制 str1 到 str3 */
    strcpy(str3, str1);
    printf("strcpy( str3, str1) :  str3=%s\n", str3);

    /* 连接 str1 和 str2 */
    strcat(str1, str2);
    printf("strcat( str1, str2):   str1=%s\n", str1);

    /* 连接后，str1 的总长度 */
    size_t len = strlen(str1);
    printf("strlen(str1) :  %zu\n", len);

    int* x = str1;

    printf("xxxx%d\n", x);

    return 0;
}