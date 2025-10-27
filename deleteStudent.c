#include <stdio.h>
#include "struct.h"
#include "funcation.h"
#include <string.h>

// 删除学生信息
void deleteStudent(STS *arr) {
    if (arr->size == 0) {
        printf("当前没有学生信息，无法删除！\n");
        return;
    }
    
    char name[20];
    printf("\n请输入要删除的学生姓名：\n");
    scanf("%s", name);
    
    int dest = findStudent(arr, name);
    if (dest == -1) {
        printf("未找到姓名为 %s 的学生！\n", name);
        return;
    }
    
    // 打印要删除的学生信息，确认删除
    printf("确定要删除以下学生信息吗？\n");
    printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
           arr->students[dest].name, arr->students[dest].id, arr->students[dest].score);
    
    char confirm;
    printf("确认删除请输入 'y'，取消删除请输入其他键：");
    scanf(" %c", &confirm);  // 注意%c前有空格，用于跳过之前的换行符
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("已取消删除操作！\n");
        return;
    }
    
    // 执行删除操作
    int i;
    for(i = dest; i < arr->size - 1; i++) {
        arr->students[i] = arr->students[i+1];
    }
    arr->size--;
    printf("学生信息删除成功！\n");
}
