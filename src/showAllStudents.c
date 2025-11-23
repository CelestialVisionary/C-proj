#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "funcation.h"

// 显示所有学生信息
void showAllStudents(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    printf("\n\t\t学生信息列表\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("%-15s %-10s %-10s %-12s %-10s %-10s\n", "姓名", "学号", "成绩", "学生卡号", "余额", "卡状态");
    printf("--------------------------------------------------------------------------------------\n");
    
    int i;
    for(i = 0; i < arr->size; i++) {
        char statusStr[10];
        if (arr->students[i].cardStatus == 1) {
            strcpy(statusStr, "正常");
        } else {
            strcpy(statusStr, "挂失");
        }
        
        printf("%-15s %-10d %-10.2f %-12d %-10.2f %-10s\n", 
               arr->students[i].name, 
               arr->students[i].id, 
               arr->students[i].score,
               arr->students[i].cardId,
               arr->students[i].balance,
               statusStr);
    }
    
    printf("--------------------------------------------------------------------------------------\n");
    printf("共有 %d 名学生\n\n", arr->size);
}
