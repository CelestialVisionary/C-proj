#include <stdio.h>
#include "struct.h"
#include "funcation.h"
#include <string.h>

// 根据姓名查找学生，返回学生索引
// 如果未找到，返回-1
int findStudent(STS *arr, char *name) {
    int i;
    for(i = 0; i < arr->size; i++) {
        if(strcmp(name, arr->students[i].name) == 0) {
            return i;  // 找到学生，返回索引
        }
    }
    return -1;  // 未找到学生
}
