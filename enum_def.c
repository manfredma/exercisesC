/*
 枚举是 C 语言中的一种基本数据类型，它可以让数据更简洁，更易读。
 枚举语法定义格式为：enum　枚举名　{枚举元素1,枚举元素2,……};
 */
#include <stdio.h>
#include <stdlib.h>

int main() {

    enum color {
        red = 1, green, blue
    };

    enum color favorite_color;

    /* 用户输入数字来选择颜色 */
    printf("请输入你喜欢的颜色: (1. red, 2. green, 3. blue): ");
    scanf("%u", &favorite_color);

    /* 输出结果 */
    switch (favorite_color) {
        case red:
            printf("你喜欢的颜色是红色");
            break;
        case green:
            printf("你喜欢的颜色是绿色");
            break;
        case blue:
            printf("你喜欢的颜色是蓝色");
            break;
        default:
            printf("你没有选择你喜欢的颜色");
    }

    printf("\n");
    enum day {
        saturday,
        sunday,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday
    };

    int a = 1;
    enum day weekend;
    weekend = (enum day) a;  //类型转换
    //weekend = a; //错误
    printf("weekend:%d", weekend);

    int a2 = weekend;
    printf("weekend2:%d", a2);
    return 0;
}