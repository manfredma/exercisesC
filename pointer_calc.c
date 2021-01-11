// C 指针是一个用数值表示的地址。因此，您可以对指针执行算术运算。可以对指针进行四种算术运算：++、--、+、-。
// 假设 ptr 是一个指向地址 1000 的整型指针，是一个 32 位的整数，让我们对该指针执行下列的算术运算：
// ptr++
// 在执行完上述的运算之后，ptr 将指向位置 1004，因为 ptr 每增加一次，它都将指向下一个整数位置，即当前位置往后移 4 字节。
// 这个运算会在不影响内存位置中实际值的情况下，移动指针到下一个内存位置。
// 如果 ptr 指向一个地址为 1000 的字符，上面的运算会导致指针指向位置 1001，因为下一个字符位置是在 1001。
// 我们概括一下：
//     指针的每一次递增，它其实会指向下一个元素的存储单元。
//     指针的每一次递减，它都会指向前一个元素的存储单元。
//     指针在递增和递减时跳跃的字节数取决于指针所指向变量数据类型长度，比如 int 就是 4 个字节。

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int MAX = 3;

double getAverage(const int *, int);

int *getRandom();

int main() {
    int var[] = {10, 100, 200};
    int i, *ptr;

    printf("\n\n使用指针加法遍历数组\n");
    /* 指针中的数组地址 */
    ptr = var;
    for (i = 0; i < MAX; i++) {

        printf("存储地址：var[%d] = %p\n", i, ptr);
        printf("存储值：var[%d] = %d\n", i, *ptr);

        /* 指向下一个位置 */
        ptr++;
    }

    printf("\n\n使用指针减法遍历数组\n");
    /* 指针中最后一个元素的地址 */
    ptr = &var[MAX - 1];
    for (i = MAX; i > 0; i--) {

        printf("存储地址：var[%d] = %p\n", i - 1, ptr);
        printf("存储值：var[%d] = %d\n", i - 1, *ptr);

        /* 指向下一个位置 */
        ptr--;
    }

    printf("\n\n使用指针加法 + 指针比较遍历数组\n");
    /* 指针中第一个元素的地址 */
    ptr = var;
    i = 0;
    while (ptr <= &var[MAX - 1]) {
        printf("存储地址：var[%d] = %p\n", i, ptr);
        printf("存储值：var[%d] = %d\n", i, *ptr);
        /* 指向下一个位置 */
        ptr++;
        i++;
    }

    printf("\n\n使用指针数组遍历数组\n");
    int *ptr2[MAX];
    for (i = 0; i < MAX; i++) {
        ptr2[i] = &var[i]; /* 赋值为整数的地址 */
    }
    for (i = 0; i < MAX; i++) {
        printf("Value of var[%d] = %d\n", i, *ptr2[i]);
    }

    printf("\n\n使用指针数组遍历数组（字符串）\n");
    const char *names[] = {
            "Zara Ali",
            "Hina Ali",
            "Nuha Ali",
            "Sara Ali",
    };

    for (i = 0; i < MAX; i++) {
        printf("Value of names[%d] = %s\n", i, names[i]);
    }

    printf("\n\n指向指针的指针\n");
    /* 指向指针的指针 */
    int V;
    int *Pt1;
    int **Pt2;

    V = 100;

    /* 获取 V 的地址 */
    Pt1 = &V;

    /* 使用运算符 & 获取 Pt1 的地址 */
    Pt2 = &Pt1;

    /* 使用 pptr 获取值 */
    printf("var = %d\n", V);
    printf("Pt1 = %p\n", Pt1);
    printf("*Pt1 = %d\n", *Pt1);
    printf("Pt2 = %p\n", Pt2);
    printf("**Pt2 = %d\n", **Pt2);

    printf("\n\n将指针作为参数传递给函数\n");
    /* 带有 5 个元素的整型数组  */
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    /* 传递一个指向数组的指针作为参数 */
    avg = getAverage(balance, 5);

    /* 输出返回值  */
    printf("Average value is: %f\n", avg);

    printf("\n\n将指针作为函数的返回值\n");
    /* 一个指向整数的指针 */
    int *p = getRandom();
    // 多输出几个未赋值的地址内容看看效果
    for (i = 0; i < 15; i++) {
        printf("*(p + [%d]) : %d\n", i, *(p + i));
    }
    return 0;
}

double getAverage(const int *arr, int size) {
    int i, sum = 0;
    double avg;
    for (i = 0; i < size; ++i) {
        sum += arr[i];
    }
    avg = (double) sum / size;
    return avg;
}

/* 要生成和返回随机数的函数 */
int *getRandom() {
    static int r[10];
    int i;

    /* 设置种子 */
    srand((unsigned) time(NULL));
    for (i = 0; i < 10; ++i) {
        r[i] = rand();
        printf("%d\n", r[i]);
    }

    return r;
}