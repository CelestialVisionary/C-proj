#ifndef STRUCT_H
#define STRUCT_H

// 定义常量
#define MAXSIZE 100  // 学生数组的最大容量

// 定义学生结构体
typedef struct {
    char name[20];  // 学生姓名
    int id;         // 学生学号
    float score;    // 学生成绩
    int cardId;     // 学生卡ID
    float balance;  // 卡余额
    int cardStatus; // 卡状态：1-正常，0-挂失
} ST;

// 定义学生数组结构体
typedef struct {
    ST students[MAXSIZE];  // 学生数组
    int size;              // 当前学生数量
} STS;

#endif