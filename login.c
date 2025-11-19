#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "funcation.h"

// 系统管理员固定账号密码
#define SYS_ADMIN_ID "admin"
#define SYS_ADMIN_PWD "123456"

// 校园卡用户登录（成功返回用户索引，失败返回-1）
int userLogin(SystemData *sys, char *userId, char *pwd) {
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("账号不存在！\n");
        return -1;
    }
    // 比较密码是否一致
    if (strcmp(sys->users[userIdx].pwd, pwd) != 0) {
        printf("密码错误！\n");
        return -1;
    }
    printf("登录成功！欢迎 %s！\n", sys->users[userIdx].name);
    return userIdx;
}

// 卡管理员登录（成功返回管理员索引，失败返回-1）
int cardAdminLogin(SystemData *sys, char *adminId, char *pwd) {
    int adminIdx = findCardAdminByAdminId(sys, adminId);
    if (adminIdx == -1) {
        printf("管理员账号不存在！\n");
        return -1;
    }
    if (strcmp(sys->cardAdmins[adminIdx].pwd, pwd) != 0) {
        printf("密码错误！\n");
        return -1;
    }
    printf("登录成功！欢迎 %s 管理员！\n", sys->cardAdmins[adminIdx].name);
    return adminIdx;
}

// 系统管理员登录（成功返回1，失败返回0）
int systemAdminLogin(char *adminId, char *pwd) {
    if (strcmp(adminId, SYS_ADMIN_ID) == 0 && strcmp(pwd, SYS_ADMIN_PWD) == 0) {
        printf("登录成功！欢迎系统管理员！\n");
        return 1;
    }
    printf("账号或密码错误！\n");
    return 0;
}
