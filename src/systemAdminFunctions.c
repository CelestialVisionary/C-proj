#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "../include/struct.h"
#include "../include/function.h"

// 新增卡管理员账号
void addCardAdmin(SystemData *sys) {
    if (sys->cardAdminCount >= MAX_CARD_ADMIN) {
        printf("卡管理员数量已达上限，无法新增！\n");
        return;
    }

    CardAdmin newAdmin;
    printf("请输入新卡管理员账号：");
    scanf("%s", newAdmin.adminId);
    // 检查账号是否已存在
    if (findCardAdminByAdminId(sys, newAdmin.adminId) != -1) {
        printf("该管理员账号已存在！\n");
        return;
    }

    // 初始密码设为123456
    strcpy(newAdmin.pwd, "123456");
    printf("请输入新卡管理员姓名：");
    scanf("%s", newAdmin.name);

    // 添加到系统
    sys->cardAdmins[sys->cardAdminCount++] = newAdmin;
    printf("新增成功！\n");
    printf("账号：%s\n", newAdmin.adminId);
    printf("初始密码：123456（提醒管理员及时修改）\n");
}

// 删除卡管理员账号
void deleteCardAdmin(SystemData *sys) {
    char adminId[ID_LEN];
    printf("请输入要删除的卡管理员账号：");
    scanf("%s", adminId);
    int adminIdx = findCardAdminByAdminId(sys, adminId);
    if (adminIdx == -1) {
        printf("未找到该卡管理员！\n");
        return;
    }

    // 确认删除
    printf("确定要删除管理员【%s（账号：%s）】吗？（y=是，n=否）：", sys->cardAdmins[adminIdx].name, adminId);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("已取消删除！\n");
        return;
    }

    // 删除：后面的管理员往前移
    for (int i = adminIdx; i < sys->cardAdminCount - 1; i++) {
        sys->cardAdmins[i] = sys->cardAdmins[i + 1];
    }
    sys->cardAdminCount--;
    printf("删除成功！\n");
}

// 查询所有用户信息
void queryAllUsers(SystemData *sys) {
    if (sys->userCount == 0) {
        printf("当前没有任何用户！\n");
        return;
    }

    printf("\n===== 所有用户信息 =====\n");
    printf("账号        姓名      校园卡号    余额（元）  状态\n");
    for (int i = 0; i < sys->userCount; i++) {
        User *user = &sys->users[i];
        printf("%s        %s      %d        %.2f      %s\n",
               user->userId,
               user->name,
               user->cardId,
               user->balance,
               user->status == 1 ? "正常" : "挂失");
    }
    printf("========================\n");
    printf("总计：%d 个用户\n", sys->userCount);
}

// 查询所有卡管理员信息
void queryAllCardAdmins(SystemData *sys) {
    if (sys->cardAdminCount == 0) {
        printf("当前没有任何卡管理员！\n");
        return;
    }

    printf("\n===== 所有卡管理员信息 =====\n");
    printf("管理员账号    姓名\n");
    for (int i = 0; i < sys->cardAdminCount; i++) {
        CardAdmin *admin = &sys->cardAdmins[i];
        printf("%s            %s\n", admin->adminId, admin->name);
    }
    printf("==========================\n");
    printf("总计：%d 个卡管理员\n", sys->cardAdminCount);
}

