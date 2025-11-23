#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../include/struct.h"
#include "../include/function.h"
#include <string.h>

// 添加学生信息
void addStudent(STS *arr) {
    if (arr->size < MAX_USER) {
        // 输入学生姓名
        printf("请输入学生姓名：");
        scanf("%s", arr->students[arr->size].name);
        
        // 输入学生学号
        printf("请输入学生学号：");
        scanf("%d", &arr->students[arr->size].id);
        
        // 输入学生成绩
        printf("请输入学生成绩：");
        scanf("%f", &arr->students[arr->size].score);
        
        // 初始化学生卡信息
        arr->students[arr->size].cardId = 100000 + arr->size; // 自动生成卡号，从100000开始
        arr->students[arr->size].balance = 0.0; // 初始余额为0
        arr->students[arr->size].cardStatus = 1; // 初始状态为正常
        
        arr->size++;
        printf("学生添加成功！\n");
        printf("已自动为学生创建学生卡，卡号：%d\n", arr->students[arr->size-1].cardId);
    } else {
        printf("学生数组已满，无法添加新学生！\n");
    }
}
