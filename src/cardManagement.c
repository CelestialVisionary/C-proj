#include <stdio.h>
#include "struct.h"
#include "funcation.h"
#include <string.h>

// 根据卡号查找学生
int findStudentByCardId(STS *arr, int cardId) {
    int i;
    for(i = 0; i < arr->size; i++) {
        if(arr->students[i].cardId == cardId) {
            return i;  // 找到学生，返回索引
        }
    }
    return -1;  // 未找到学生
}

// 学生卡充值
void rechargeCard(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int cardId;
    printf("请输入学生卡号：");
    scanf("%d", &cardId);
    
    int index = findStudentByCardId(arr, cardId);
    if (index == -1) {
        printf("未找到卡号为 %d 的学生卡！\n", cardId);
        return;
    }
    
    if (arr->students[index].cardStatus == 0) {
        printf("该卡已挂失，无法充值！\n");
        return;
    }
    
    float amount;
    printf("请输入充值金额：");
    scanf("%f", &amount);
    
    if (amount <= 0) {
        printf("充值金额必须大于0！\n");
        return;
    }
    
    arr->students[index].balance += amount;
    printf("充值成功！当前余额：%.2f\n", arr->students[index].balance);
}

// 挂失学生卡
void reportLostCard(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int cardId;
    printf("请输入要挂失的学生卡号：");
    scanf("%d", &cardId);
    
    int index = findStudentByCardId(arr, cardId);
    if (index == -1) {
        printf("未找到卡号为 %d 的学生卡！\n", cardId);
        return;
    }
    
    if (arr->students[index].cardStatus == 0) {
        printf("该卡已经处于挂失状态！\n");
        return;
    }
    
    // 确认挂失
    char confirm;
    printf("确定要挂失 %s 的学生卡吗？(y/n)：", arr->students[index].name);
    scanf(" %c", &confirm);
    
    if (confirm == 'y' || confirm == 'Y') {
        arr->students[index].cardStatus = 0;
        printf("学生卡挂失成功！\n");
    } else {
        printf("已取消挂失操作！\n");
    }
}

// 恢复学生卡
void restoreCard(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    int cardId;
    printf("请输入要恢复的学生卡号：");
    scanf("%d", &cardId);
    
    int index = findStudentByCardId(arr, cardId);
    if (index == -1) {
        printf("未找到卡号为 %d 的学生卡！\n", cardId);
        return;
    }
    
    if (arr->students[index].cardStatus == 1) {
        printf("该卡已经处于正常状态！\n");
        return;
    }
    
    arr->students[index].cardStatus = 1;
    printf("学生卡恢复成功！\n");
}

// 查询学生卡信息
void queryCardInfo(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息！\n");
        return;
    }
    
    printf("请选择查询方式：\n");
    printf("1. 按学号查询\n");
    printf("2. 按卡号查询\n");
    int choice;
    scanf("%d", &choice);
    
    int index = -1;
    
    if (choice == 1) {
        int id;
        printf("请输入学生学号：");
        scanf("%d", &id);
        index = findStudentById(arr, id);
    } else if (choice == 2) {
        int cardId;
        printf("请输入学生卡号：");
        scanf("%d", &cardId);
        index = findStudentByCardId(arr, cardId);
    } else {
        printf("输入错误，请重新输入！\n");
        return;
    }
    
    if (index == -1) {
        printf("未找到该学生信息！\n");
        return;
    }
    
    printf("\n学生卡信息：\n");
    printf("姓名：%s\n", arr->students[index].name);
    printf("学号：%d\n", arr->students[index].id);
    printf("卡号：%d\n", arr->students[index].cardId);
    printf("余额：%.2f\n", arr->students[index].balance);
    printf("卡状态：%s\n", arr->students[index].cardStatus == 1 ? "正常" : "挂失");
}