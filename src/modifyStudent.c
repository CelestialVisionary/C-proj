#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "../include/struct.h"
#include "../include/function.h"
#include <string.h>

// 修改学生信息
void modifyStudent(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息，无法修改！\n");
        return;
    }
    
    int choice;
    printf("请选择查找方式：\n");
    printf("1. 按姓名查找\n");
    printf("2. 按学号查找\n");
    printf("请输入您的选择：");
    scanf("%d", &choice);
    
    int index = -1;
    
    if (choice == 1) {
        char name[20];
        printf("请输入要修改的学生姓名：");
        scanf("%s", name);
        index = findStudent(arr, name);
    } else if (choice == 2) {
        int id;
        printf("请输入要修改的学生学号：");
        scanf("%d", &id);
        index = findStudentById(arr, id);
    } else {
        printf("输入错误，返回主菜单！\n");
        return;
    }
    
    if (index == -1) {
        printf("未找到该学生！\n");
        return;
    }
    
    // 显示当前学生信息
    printf("当前学生信息：\n");
    printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
           arr->students[index].name, 
           arr->students[index].id, 
           arr->students[index].score);
    
    // 输入新的学生信息
    printf("请输入新的学生信息（直接回车跳过不修改的字段）：\n");
    
    char newName[20];
    int newId;
    float newScore;
    
    printf("姓名（当前：%s）：", arr->students[index].name);
    scanf("%s", newName);
    if (strcmp(newName, "") != 0) {
        strcpy(arr->students[index].name, newName);
    }
    
    printf("学号（当前：%d）：", arr->students[index].id);
    scanf("%d", &newId);
    if (newId > 0) {
        arr->students[index].id = newId;
    }
    
    printf("成绩（当前：%.2f）：", arr->students[index].score);
    scanf("%f", &newScore);
    if (newScore >= 0 && newScore <= 100) {
        arr->students[index].score = newScore;
    }
    
    printf("学生信息修改成功！\n");
}