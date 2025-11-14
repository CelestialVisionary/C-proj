#include <stdio.h>
#include <windows.h>
#include "struct.h"
#include "funcation.h"

// 显示角色选择菜单
void showRoleMenu() {
    printf("\n===== 校园卡管理系统 =====\n");
    printf("请选择用户角色\n");
    printf("1. 校园卡用户\n");
    printf("2. 卡务管理员\n");
    printf("3. 系统管理员\n");
    printf("0. 退出系统\n");
    printf("==========================\n");
    printf("请输入您的选择(0-3)：");
}

// 显示校园卡用户菜单
void showUserMenu() {
    printf("\n===== 校园卡用户菜单 =====\n");
    printf("1. 密码修改\n");
    printf("2. 查询余额\n");
    printf("3. 查询消费记录\n");
    printf("4. 挂失/解挂校园卡\n");
    printf("0. 退出登录（返回主菜单）\n");
    printf("==========================\n");
    printf("请输入您的选择(0-4)：");
}

// 显示卡务管理员菜单
void showCardAdminMenu() {
    printf("\n===== 卡务管理员菜单 =====\n");
    printf("1. 创建用户\n");
    printf("2. 校园卡充值\n");
    printf("3. 用户信息查询及修改\n");
    printf("4. 校园卡密码重置\n");
    printf("5. 校园卡密码修改\n");
    printf("6. 挂失/解挂\n");
    printf("7. 校园卡注销\n");
    printf("0. 退出登录（返回主菜单）\n");
    printf("==========================\n");
    printf("请输入您的选择(0-7)：");
}

// 显示系统管理员菜单
void showSystemAdminMenu() {
    printf("\n===== 系统管理员菜单 =====\n");
    printf("1. 添加卡务管理员账号\n");
    printf("2. 删除卡务管理员账号\n");
    printf("3. 查询所有用户信息\n");
    printf("4. 查询所有卡务管理员信息\n");
    printf("0. 退出登录（返回主菜单）\n");
    printf("==========================\n");
    printf("请输入您的选择(0-5)：");
}

int main() {
    SystemData sys;
    initSystem(&sys); // 初始化系统

    int roleChoice;
    while (1) {
        showRoleMenu();
        scanf("%d", &roleChoice);

        // 校园卡用户
        if (roleChoice == 1) {
            int isLogin = 0;       // 是否登录成功
            int userIdx = -1;      // 登录用户索引
            int roleActive = 1;    // 控制角色内循环（是否返回主菜单）
            while (roleActive) {
                if (!isLogin) {
                    // 未登录时强制先登录
                    char userId[ID_LEN], pwd[PWD_LEN];
                    printf("\n===== 校园卡用户登录 =====\n");
                    printf("请输入账号(学号)：");
                    scanf("%s", userId);
                    printf("请输入密码：");
                    scanf("%s", pwd);
                    userIdx = userLogin(&sys, userId, pwd);
                    if (userIdx != -1) {
                        isLogin = 1; // 登录成功后进入功能菜单
                    }
                    printf("按回车继续...");
                    getchar();
                    getchar();
                } else {
                    // 已登录显示功能菜单
                    showUserMenu();
                    int userChoice;
                    scanf("%d", &userChoice);

                    switch (userChoice) {
                        case 1: changeOwnPwd(&sys, userIdx); break;
                        case 2: queryOwnBalance(&sys, userIdx); break;
                        case 3: queryOwnConsumption(&sys, userIdx); break;
                        case 4: toggleOwnCardStatus(&sys, userIdx); break;
                        case 0:
                            printf("退出登录成功，返回主菜单！\n");
                            isLogin = 0;
                            roleActive = 0; // 退出角色内循环，返回主菜单
                            break;
                        default: printf("输入错误，请重新选择！\n"); break;
                    }

                    if (isLogin) { // 未退出时等待回车
                        printf("按回车继续...");
                        getchar();
                        getchar();
                    }
                }
            }
        }

        // 卡务管理员
        else if (roleChoice == 2) {
            int isLogin = 0;
            int adminIdx = -1;
            int roleActive = 1;
            while (roleActive) {
                if (!isLogin) {
                    // 未登录时强制先登录
                    char adminId[ID_LEN], pwd[PWD_LEN];
                    printf("\n===== 卡务管理员登录 =====\n");
                    printf("请输入管理员账号：");
                    scanf("%s", adminId);
                    printf("请输入密码：");
                    scanf("%s", pwd);
                    adminIdx = cardAdminLogin(&sys, adminId, pwd);
                    if (adminIdx != -1) {
                        isLogin = 1;
                    }
                    printf("按回车继续...");
                    getchar();
                    getchar();
                } else {
                    showCardAdminMenu();
                    int adminChoice;
                    scanf("%d", &adminChoice);

                    switch (adminChoice) {
                        case 1: createUser(&sys); break;
                        case 2: rechargeCard(&sys); break;
                        case 3: queryAndModifyUser(&sys); break;
                        case 4: resetUserPwd(&sys); break;
                        case 5: modifyUserPwdByAdmin(&sys); break;
                        case 6: toggleUserCardStatusByAdmin(&sys); break;
                        case 7: cancelUserAccount(&sys); break;
                        case 0:
                            printf("退出登录成功，返回主菜单！\n");
                            isLogin = 0;
                            roleActive = 0; // 返回主菜单
                            break;
                        default: printf("输入错误，请重新选择！\n"); break;
                    }

                    if (isLogin) {
                        printf("按回车继续...");
                        getchar();
                        getchar();
                    }
                }
            }
        }

        // 系统管理员
        else if (roleChoice == 3) {
            int isLogin = 0;
            int roleActive = 1;
            while (roleActive) {
                if (!isLogin) {
                    // 未登录时强制先登录
                    char adminId[ID_LEN], pwd[PWD_LEN];
                    printf("\n===== 系统管理员登录 =====\n");
                    printf("请输入管理员账号：");
                    scanf("%s", adminId);
                    printf("请输入密码：");
                    scanf("%s", pwd);
                    if (systemAdminLogin(adminId, pwd)) {
                        isLogin = 1;
                    }
                    printf("按回车继续...");
                    getchar();
                    getchar();
                } else {
                    showSystemAdminMenu();
                    int sysChoice;
                    scanf("%d", &sysChoice);

                    switch (sysChoice) {
                        case 1: addCardAdmin(&sys); break;
                        case 2: deleteCardAdmin(&sys); break;
                        case 3: queryAllUsers(&sys); break;
                        case 4: queryAllCardAdmins(&sys); break;
                        case 0:
                            printf("退出登录成功，返回主菜单！\n");
                            isLogin = 0;
                            roleActive = 0; // 返回主菜单
                            break;
                        default: printf("输入错误，请重新选择！\n"); break;
                    }

                    if (isLogin) {
                        printf("按回车继续...");
                        getchar();
                        getchar();
                    }
                }
            }
        }

        // 退出系统
        else if (roleChoice == 0) {
            printf("感谢使用校园卡管理系统，再见！\n");
            return 0;
        }

        // 输入错误
        else {
            printf("输入错误，请重新选择！\n");
            printf("按回车继续...");
            getchar();
            getchar();
        }
    }

    return 0;
}
