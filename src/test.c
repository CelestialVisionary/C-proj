#include <stdio.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "funcation.h"

// Missing function implementations needed for the test
// Sort users by balance (ascending)
void sortUsersByBalance(SystemData *sys) {
    for (int i = 0; i < sys->userCount - 1; i++) {
        for (int j = 0; j < sys->userCount - i - 1; j++) {
            if (sys->users[j].balance > sys->users[j + 1].balance) {
                // Swap users
                User temp = sys->users[j];
                sys->users[j] = sys->users[j + 1];
                sys->users[j + 1] = temp;
            }
        }
    }
}

// Find records by card ID
int findRecordsByCardId(SystemData *sys, int cardId, TransRecord result[], int *resCount) {
    *resCount = 0;
    for (int i = 0; i < sys->recordCount; i++) {
        if (sys->records[i].cardId == cardId) {
            result[(*resCount)++] = sys->records[i];
        }
    }
    return *resCount;
}

// Sort records by time (descending)
void sortRecordsByTime(SystemData *sys) {
    for (int i = 0; i < sys->recordCount - 1; i++) {
        for (int j = 0; j < sys->recordCount - i - 1; j++) {
            // Compare time strings lexicographically (assuming YYYY-MM-DD HH:MM:SS format)
            if (strcmp(sys->records[j].time, sys->records[j + 1].time) < 0) {
                // Swap records
                TransRecord temp = sys->records[j];
                sys->records[j] = sys->records[j + 1];
                sys->records[j + 1] = temp;
            }
        }
    }
}

// Sort admins by admin ID (ascending)
void sortAdminsByAdminId(SystemData *sys) {
    for (int i = 0; i < sys->cardAdminCount - 1; i++) {
        for (int j = 0; j < sys->cardAdminCount - i - 1; j++) {
            if (strcmp(sys->cardAdmins[j].adminId, sys->cardAdmins[j + 1].adminId) > 0) {
                // Swap admins
                CardAdmin temp = sys->cardAdmins[j];
                sys->cardAdmins[j] = sys->cardAdmins[j + 1];
                sys->cardAdmins[j + 1] = temp;
            }
        }
    }
}

// Test user data structure
void testUserStruct(SystemData *sys) {
    printf("===测试用户数据结构===
");
    // Add test users
    strcpy(sys->users[0].userId, "2023001");
    strcpy(sys->users[0].name, "张三");
    sys->users[0].balance = 100.5;
    sys->users[0].status = 0;

    strcpy(sys->users[1].userId, "2023002");
    strcpy(sys->users[1].name, "李四");
    sys->users[1].balance = 50.0;
    sys->users[1].status = 0;
    sys->userCount = 2;

    // Test finding a user
    int userIdx = findUserByUserId(sys, "2023001");
    if (userIdx != -1) {
        User* user = &sys->users[userIdx];
        printf("找到用户：%s（余额：%.1f）\n", user->name, user->balance);
    } else {
        printf("未找到用户\n");
    }

    // Test sorting by balance (ascending)
    sortUsersByBalance(sys);
    printf("排序后用户余额：%.1f, %.1f\n", sys->users[0].balance, sys->users[1].balance);
}

// Test transaction record data structure
void testRecordStruct(SystemData *sys) {
    printf("\n===测试交易记录数据结构===
");
    // Add test records
    sys->records[0].cardId = 100001;
    sys->records[0].type = RECHARGE;
    sys->records[0].amount = 200;
    strcpy(sys->records[0].time, "2023-10-01 09:00:00");

    sys->records[1].cardId = 100001;
    sys->records[1].type = CONSUMPTION;
    sys->records[1].amount = 30;
    strcpy(sys->records[1].time, "2023-10-02 14:30:00");
    sys->recordCount = 2;

    // Test finding records by card ID
    TransRecord result[10];
    int resCount;
    findRecordsByCardId(sys, 100001, result, &resCount);
    printf("找到%d条记录：\n", resCount);
    for (int i = 0; i < resCount; i++) {
        printf("%s %s %.1f\n", result[i].time, result[i].type == RECHARGE ? "充值" : "消费", result[i].amount);
    }

    // Test sorting by time (descending)
    sortRecordsByTime(sys);
    printf("排序后时间：%s, %s\n", sys->records[0].time, sys->records[1].time);
}

// Test administrator data structure
void testAdminStruct(SystemData *sys) {
    printf("\n===测试管理员数据结构===
");
    // Add test administrators
    strcpy(sys->cardAdmins[0].adminId, "A002");
    strcpy(sys->cardAdmins[0].pwd, "123456");
    strcpy(sys->cardAdmins[0].name, "管理员2");

    strcpy(sys->cardAdmins[1].adminId, "A001");
    strcpy(sys->cardAdmins[1].pwd, "123456");
    strcpy(sys->cardAdmins[1].name, "管理员1");
    sys->cardAdminCount = 2;

    // Test finding an administrator by adminId
    int adminIdx = findCardAdminByAdminId(sys, "A001");
    if (adminIdx != -1) {
        CardAdmin* admin = &sys->cardAdmins[adminIdx];
        printf("找到管理员：%s\n", admin->adminId);
    } else {
        printf("未找到管理员\n");
    }

    // Test sorting by adminId (ascending)
    sortAdminsByAdminId(sys);
    printf("排序后账号：%s, %s\n", sys->cardAdmins[0].adminId, sys->cardAdmins[1].adminId);
}

int main() {
    SystemData sys;
    initSystem(&sys);

    testUserStruct(&sys);
    testRecordStruct(&sys);
    testAdminStruct(&sys);

    return 0;
}