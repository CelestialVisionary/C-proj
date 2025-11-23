#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../include/struct.h"
#include "../include/function.h"

// 按学号排序学生信息（冒泡排序）
void sortStudentsById(STS *arr) {
    if (arr->size <= 1) {
        printf("学生数量不足或只有一名学生，无需排序！\n");
        return;
    }
    
    int i, j;
    ST temp;  // 临时变量，用于交换学生信息
    
    for(i = 0; i < arr->size - 1; i++) {
        for(j = 0; j < arr->size - 1 - i; j++) {
            if(arr->students[j].id > arr->students[j+1].id) {
                // 交换两个学生的信息
                temp = arr->students[j];
                arr->students[j] = arr->students[j+1];
                arr->students[j+1] = temp;
            }
        }
    }
    
    printf("学生信息已按学号排序完成！\n");
}