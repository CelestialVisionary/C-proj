#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../include/struct.h"
#include "../include/function.h"

// 根据学号查找学生，返回学生索引
// 如果未找到，返回-1
int findStudentById(STS *arr, int id) {
    int i;
    for(i = 0; i < arr->size; i++) {
        if(arr->students[i].id == id) {
            return i;  // 找到学生，返回索引
        }
    }
    return -1;  // 未找到学生
}