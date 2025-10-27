#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "struct.h"
#include "funcation.h"

// 显示角色选择菜单
void showRoleMenu() {
    printf("\n\t\t===== 学生管理系统 =====\n");
    printf("\t\t请选择用户角色\n");
    printf("\t\t1. 学生\n");
    printf("\t\t2. 卡管理员\n");
    printf("\t\t3. 系统管理员\n");
    printf("\t\t0. 退出系统\n");
    printf("\t\t======================\n");
    printf("请输入您的选择(0-3)：");
}

// 显示学生菜单
void showNormalUserMenu() {
    printf("\n\t\t===== 学生菜单 =====\n");
    printf("\t\t1. 查看我的信息\n");
    printf("\t\t2. 查询我的卡片信息\n");
    printf("\t\t0. 返回角色选择\n");
    printf("\t\t======================\n");
    printf("请输入您的选择(0-2)：");
}

// 显示卡管理员菜单
void showCardAdminMenu() {
    printf("\n\t\t===== 卡管理员菜单 =====\n");
    printf("\t\t1. 添加学生信息\n");
    printf("\t\t2. 查找学生信息\n");
    printf("\t\t3. 修改学生信息\n");
    printf("\t\t4. 显示所有学生信息\n");
    printf("\t\t5. 学生卡充值\n");
    printf("\t\t6. 挂失学生卡\n");
    printf("\t\t7. 恢复学生卡\n");
    printf("\t\t8. 查询学生卡信息\n");
    printf("\t\t0. 返回角色选择\n");
    printf("\t\t======================\n");
    printf("请输入您的选择(0-8)：");
}

// 显示系统管理员菜单
void showSystemAdminMenu() {
    printf("\n\t\t===== 系统管理员菜单 =====\n");
    printf("\t\t1. 添加学生信息\n");
    printf("\t\t2. 查找学生信息\n");
    printf("\t\t3. 删除学生信息\n");
    printf("\t\t4. 修改学生信息\n");
    printf("\t\t5. 按学号排序\n");
    printf("\t\t6. 显示所有学生信息\n");
    printf("\t\t7. 学生卡充值\n");
    printf("\t\t8. 挂失学生卡\n");
    printf("\t\t9. 恢复学生卡\n");
    printf("\t\t10. 查询学生卡信息\n");
    printf("\t\t0. 返回角色选择\n");
    printf("\t\t==========================\n");
    printf("请输入您的选择(0-10)：");
}

// 显示查找菜单
void showFindMenu() {
    printf("\n\t\t===== 查找学生 =====\n");
    printf("\t\t1. 按姓名查找\n");
    printf("\t\t2. 按学号查找\n");
    printf("\t\t0. 返回主菜单\n");
    printf("\t\t====================\n");
    printf("请输入您的选择(0-2)：");
}

int main() {
    // 设置控制台输出编码为UTF-8，解决中文显示乱码问题
    SetConsoleOutputCP(CP_UTF8);
    
    STS students;
    initStudentArray(&students);  // 初始化学生数组
    
    int roleChoice;
    while(1) {
        showRoleMenu();  // 显示角色选择菜单
        scanf("%d", &roleChoice);
        
        switch(roleChoice) {
            case 1:  // 普通用户
                {
                    int normalChoice;
                    while(1) {
                        showNormalUserMenu();
                        scanf("%d", &normalChoice);
                        
                        switch(normalChoice) {
                            case 1:  // 查看我的信息
                                printf("\n请输入您的学号：");
                                int id;
                                scanf("%d", &id);
                                int index = findStudentById(&students, id);
                                if (index != -1) {
                                    printf("\n\t\t个人信息查询结果\n");
                                    printf("姓名：%s\n", students.students[index].name);
                                    printf("学号：%d\n", students.students[index].id);
                                    printf("成绩：%.2f\n", students.students[index].score);
                                    printf("学生卡号：%d\n", students.students[index].cardId);
                                    printf("卡余额：%.2f\n", students.students[index].balance);
                                    printf("卡状态：%s\n", students.students[index].cardStatus ? "正常" : "挂失");
                                } else {
                                    printf("未找到该学生信息！\n");
                                }
                                break;
                            case 2:  // 查询我的卡片信息
                                printf("\n请输入您的学生卡号：");
                                int cardId;
                                scanf("%d", &cardId);
                                int cardIndex = findStudentByCardId(&students, cardId);
                                if (cardIndex != -1) {
                                    printf("\n\t\t卡片信息查询结果\n");
                                    printf("姓名：%s\n", students.students[cardIndex].name);
                                    printf("学号：%d\n", students.students[cardIndex].id);
                                    printf("学生卡号：%d\n", students.students[cardIndex].cardId);
                                    printf("卡余额：%.2f\n", students.students[cardIndex].balance);
                                    printf("卡状态：%s\n", students.students[cardIndex].cardStatus ? "正常" : "挂失");
                                } else {
                                    printf("未找到该卡片信息！\n");
                                }
                                break;
                            case 0:  // 返回角色选择
                                break;
                            default:
                                printf("输入错误，请重新输入！\n");
                                break;
                        }
                        
                        if (normalChoice == 0) break;
                        
                        // 暂停，让用户看清楚输出结果
                        printf("\n按回车键继续...");
                        getchar();  // 消耗之前的换行符
                        getchar();  // 等待用户输入回车键
                    }
                }
                break;
            case 2:  // 卡管理员
                {
                    int cardAdminChoice;
                    while(1) {
                        showCardAdminMenu();
                        scanf("%d", &cardAdminChoice);
                        
                        switch(cardAdminChoice) {
                            case 1:  // 添加学生信息
                                addStudent(&students);
                                break;
                            case 2:  // 查找学生信息
                                if (students.size == 0) {
                                    printf("当前没有学生信息！\n");
                                    break;
                                }
                                
                                int findChoice;
                                showFindMenu();
                                scanf("%d", &findChoice);
                                
                                switch(findChoice) {
                                    case 1:  // 按姓名查找
                                        {
                                            char name[20];
                                            printf("请输入要查找的学生姓名：");
                                            scanf("%s", name);
                                            
                                            int index = findStudent(&students, name);
                                            if (index == -1) {
                                                printf("未找到姓名为 %s 的学生！\n", name);
                                            } else {
                                                printf("\n找到学生信息：\n");
                                                printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
                                                       students.students[index].name, 
                                                       students.students[index].id, 
                                                       students.students[index].score);
                                            }
                                        }
                                        break;
                                    case 2:  // 按学号查找
                                        {
                                            int id;
                                            printf("请输入要查找的学生学号：");
                                            scanf("%d", &id);
                                            
                                            int index = findStudentById(&students, id);
                                            if (index == -1) {
                                                printf("未找到学号为 %d 的学生！\n", id);
                                            } else {
                                                printf("\n找到学生信息：\n");
                                                printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
                                                       students.students[index].name, 
                                                       students.students[index].id, 
                                                       students.students[index].score);
                                            }
                                        }
                                        break;
                                    case 0:  // 返回卡管理员菜单
                                        break;
                                    default:
                                        printf("输入错误，请重新输入！\n");
                                        break;
                                }
                                break;
                            case 3:  // 修改学生信息
                                modifyStudent(&students);
                                break;
                            case 4:  // 显示所有学生信息
                                showAllStudents(&students);
                                break;
                            case 5:  // 学生卡充值
                                rechargeCard(&students);
                                break;
                            case 6:  // 挂失学生卡
                                reportLostCard(&students);
                                break;
                            case 7:  // 恢复学生卡
                                restoreCard(&students);
                                break;
                            case 8:  // 查询学生卡信息
                                queryCardInfo(&students);
                                break;
                            case 0:  // 返回角色选择
                                break;
                            default:
                                printf("输入错误，请重新输入！\n");
                                break;
                        }
                        
                        if (cardAdminChoice == 0) break;
                        
                        // 暂停，让用户看清楚输出结果
                        printf("\n按回车键继续...");
                        getchar();  // 消耗之前的换行符
                        getchar();  // 等待用户输入回车键
                    }
                }
                break;
            case 3:  // 系统管理员
                {
                    int systemAdminChoice;
                    while(1) {
                        showSystemAdminMenu();
                        scanf("%d", &systemAdminChoice);
                        
                        switch(systemAdminChoice) {
                            case 1:  // 添加学生信息
                                addStudent(&students);
                                break;
                            case 2:  // 查找学生信息
                                if (students.size == 0) {
                                    printf("当前没有学生信息！\n");
                                    break;
                                }
                                
                                int findChoice;
                                showFindMenu();
                                scanf("%d", &findChoice);
                                
                                switch(findChoice) {
                                    case 1:  // 按姓名查找
                                        {
                                            char name[20];
                                            printf("请输入要查找的学生姓名：");
                                            scanf("%s", name);
                                            
                                            int index = findStudent(&students, name);
                                            if (index == -1) {
                                                printf("未找到姓名为 %s 的学生！\n", name);
                                            } else {
                                                printf("\n找到学生信息：\n");
                                                printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
                                                       students.students[index].name, 
                                                       students.students[index].id, 
                                                       students.students[index].score);
                                            }
                                        }
                                        break;
                                    case 2:  // 按学号查找
                                        {
                                            int id;
                                            printf("请输入要查找的学生学号：");
                                            scanf("%d", &id);
                                            
                                            int index = findStudentById(&students, id);
                                            if (index == -1) {
                                                printf("未找到学号为 %d 的学生！\n", id);
                                            } else {
                                                printf("\n找到学生信息：\n");
                                                printf("姓名：%s\t学号：%d\t成绩：%.2f\n", 
                                                       students.students[index].name, 
                                                       students.students[index].id, 
                                                       students.students[index].score);
                                            }
                                        }
                                        break;
                                    case 0:  // 返回系统管理员菜单
                                        break;
                                    default:
                                        printf("输入错误，请重新输入！\n");
                                        break;
                                }
                                break;
                            case 3:  // 删除学生信息
                                deleteStudent(&students);
                                break;
                            case 4:  // 修改学生信息
                                modifyStudent(&students);
                                break;
                            case 5:  // 按学号排序
                                sortStudentsById(&students);
                                break;
                            case 6:  // 显示所有学生信息
                                showAllStudents(&students);
                                break;
                            case 7:  // 学生卡充值
                                rechargeCard(&students);
                                break;
                            case 8:  // 挂失学生卡
                                reportLostCard(&students);
                                break;
                            case 9:  // 恢复学生卡
                                restoreCard(&students);
                                break;
                            case 10:  // 查询学生卡信息
                                queryCardInfo(&students);
                                break;
                            case 0:  // 返回角色选择
                                break;
                            default:
                                printf("输入错误，请重新输入！\n");
                                break;
                        }
                        
                        if (systemAdminChoice == 0) break;
                        
                        // 暂停，让用户看清楚输出结果
                        printf("\n按回车键继续...");
                        getchar();  // 消耗之前的换行符
                        getchar();  // 等待用户输入回车键
                    }
                }
                break;
            case 0:  // 退出系统
                printf("感谢使用学生管理系统，再见！\n");
                return 0;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
        
        // 暂停，让用户看清楚输出结果
        printf("\n按回车键继续...");
        getchar();  // 消耗之前的换行符
        getchar();  // 等待用户输入回车键
    }
    
    return 0;
}
