#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "../include/struct.h"
#include "../include/function.h"

// 修改自己的密码
void changeOwnPwd(SystemData *sys, int userIdx) {
    char oldPwd[PWD_LEN], newPwd[PWD_LEN], confirmPwd[PWD_LEN];
    User *user = &sys->users[userIdx]; // 当前登录用户

    printf("请输入旧密码：");
    scanf("%s", oldPwd);
    // 先验证旧密码
    if (strcmp(user->pwd, oldPwd) != 0) {
        printf("旧密码错误，修改失败！\n");
        return;
    }

    // 输入新密码并确认
    printf("请输入新密码：");
    scanf("%s", newPwd);
    printf("请再次输入新密码：");
    scanf("%s", confirmPwd);

    // 检查两次密码是否一致
    if (strcmp(newPwd, confirmPwd) != 0) {
        printf("两次密码不一致，修改失败！\n");
        return;
    }

    // 密码修改成功
    strcpy(user->pwd, newPwd);
    printf("密码修改成功！下次登录请用新密码！\n");
}

// 查询自己的余额
void queryOwnBalance(SystemData *sys, int userIdx) {
    // 直接获取当前用户的余额并打印
    float balance = sys->users[userIdx].balance;
    printf("你的校园卡当前余额：%.2f 元\n", balance);
}

// 查询自己的消费记录
void queryOwnConsumption(SystemData *sys, int userIdx) {
    int cardId = sys->users[userIdx].cardId;
    int count = 0; // 统计消费记录条数

    printf("\n===== 你的消费记录 =====\n");
    printf("时间                类型    金额（元）\n");
    // 遍历所有交易记录，找当前用户的消费记录
    for (int i = 0; i < sys->recordCount; i++) {
        TransRecord *rec = &sys->records[i];
        // 只显示消费类型的记录
        if (rec->cardId == cardId && rec->type == CONSUMPTION) {
            count++;
            printf("%s    消费    %.2f\n", rec->time, rec->amount);
        }
    }

    if (count == 0) {
        printf("暂无消费记录！\n");
    }
    printf("========================\n");
}

// 挂失/解挂自己的卡（状态切换）
void toggleOwnCardStatus(SystemData *sys, int userIdx) {
    User *user = &sys->users[userIdx];
    if (user->status == 1) {
        // 正常状态 →挂失
        user->status = 0;
        printf("校园卡挂失成功！挂失期间不能消费和充值！\n");
    } else {
        // 挂失状态 →解挂
        user->status = 1;
        printf("校园卡解挂成功！可以正常使用了！\n");
    }
}
