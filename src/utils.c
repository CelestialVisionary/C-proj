#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/struct.h"
#include "../include/function.h"

// 初始化系统：设置初始值，添加测试账号（方便直接测试）
void initSystem(SystemData *sys) {
    // 所有数量初始化为0
    sys->userCount = 0;
    sys->cardAdminCount = 0;
    sys->recordCount = 0;

    // 添加测试卡管理员（账号：cardadmin，密码：123456）
    CardAdmin testAdmin;
    strcpy(testAdmin.adminId, "cardadmin");
    strcpy(testAdmin.pwd, "123456");
    strcpy(testAdmin.name, "Zhang Admin");
    sys->cardAdmins[sys->cardAdminCount++] = testAdmin;

    // 添加测试校园卡用户（账号：2024001，密码：123456）
    User testUser;
    strcpy(testUser.userId, "2024001");
    strcpy(testUser.pwd, "123456");
    strcpy(testUser.name, "Li Si");
    testUser.cardId = 100001;  // 校园卡号从100001开始
    testUser.balance = 200.0f; // 初始余额200元
    testUser.status = 1;       // 初始状态正常
    sys->users[sys->userCount++] = testUser;

    // 添加测试交易记录（充值200元，消费30元）
    saveTransRecord(sys, 100001, RECHARGE, 200.0f);
    saveTransRecord(sys, 100001, CONSUMPTION, 30.0f);

    printf("系统初始化完成！\n");
    printf("测试账号：\n");
    printf("用户：账号2024001 / 密码123456\n");
    printf("卡管理员：账号cardadmin / 密码123456\n");
    printf("系统管理员：账号admin / 密码123456\n");
}

// 按用户账号找用户（找到返回索引，没找到返回-1）
int findUserByUserId(SystemData *sys, char *userId) {
    for (int i = 0; i < sys->userCount; i++) {
        // 比较账号是否一致
        if (strcmp(sys->users[i].userId, userId) == 0) {
            return i;
        }
    }
    return -1;
}

// 按校园卡号找用户（找到返回索引，没找到返回-1）
int findUserByCardId(SystemData *sys, int cardId) {
    for (int i = 0; i < sys->userCount; i++) {
        if (sys->users[i].cardId == cardId) {
            return i;
        }
    }
    return -1;
}

// 按管理员账号找卡管理员（找到返回索引，没找到返回-1）
int findCardAdminByAdminId(SystemData *sys, char *adminId) {
    for (int i = 0; i < sys->cardAdminCount; i++) {
        if (strcmp(sys->cardAdmins[i].adminId, adminId) == 0) {
            return i;
        }
    }
    return -1;
}

// 获取当前时间（格式：YYYY-MM-DD HH:MM:SS）
void getCurrentTime(char *timeStr) {
    time_t now = time(NULL);
    struct tm *tmInfo = localtime(&now);
    // 直接格式化时间字符串，不用深究原理
    sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d",
            tmInfo->tm_year + 1900, tmInfo->tm_mon + 1, tmInfo->tm_mday,
            tmInfo->tm_hour, tmInfo->tm_min, tmInfo->tm_sec);
}

// 保存交易记录（消费/充值后调用）
void saveTransRecord(SystemData *sys, int cardId, TransType type, float amount) {
    // 先判断记录是否满了
    if (sys->recordCount >= MAX_RECORD) {
        printf("交易记录已满，保存失败！\n");
        return;
    }
    // 新增一条记录
    TransRecord *newRecord = &sys->records[sys->recordCount];
    newRecord->cardId = cardId;
    newRecord->type = type;
    newRecord->amount = amount;
    getCurrentTime(newRecord->time); // 记录当前时间
    sys->recordCount++; // 记录数+1
}
