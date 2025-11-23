#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../include/struct.h"
#include "../include/function.h"

// 初始化学生数组
void initStudentArray(STS *arr) {
    arr->size = 0;  // 初始化学生数量为0
    printf("学生数组初始化成功！\n");
}