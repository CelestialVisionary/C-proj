#ifndef FUNCATION_H
#define FUNCATION_H

#include "struct.h"

// 菜单显示函数
void showRoleMenu();
void showNormalUserMenu();
void showCardAdminMenu();
void showSystemAdminMenu();

// 卡片管理相关函数
int findStudentByCardId(STS *arr, int cardId);
void rechargeCard(STS *arr);
void reportLostCard(STS *arr);
void restoreCard(STS *arr);
void queryCardInfo(STS *arr);

// 初始化学生数组
void initStudentArray(STS *arr);

// 添加学生信息
void addStudent(STS *arr);

// 根据姓名查找学生，返回学生索引（未找到返回-1）
int findStudent(STS *arr, char *name);

// 根据学号查找学生，返回学生索引（未找到返回-1）
int findStudentById(STS *arr, int id);

// 删除学生信息
void deleteStudent(STS *arr);

// 修改学生信息
void modifyStudent(STS *arr);

// 按学号排序学生信息
void sortStudentsById(STS *arr);

// 显示所有学生信息
void showAllStudents(STS *arr);

#endif