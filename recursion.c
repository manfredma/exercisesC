//
// Created by 马兴方 on 2021/3/30.
//
#include <stdio.h>
double recursiveAll(int depth);

double recursiveAll(int depth) {
    if (depth < 1) {

    }
    printf("%d \n", depth);
    return recursiveAll(depth + 1);
}

int main() {

    recursiveAll(1);
}


