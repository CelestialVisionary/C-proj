#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "funcation.h"

// 开户办理（新增校园卡用户）
void createUser(SystemData *sys) {
    // 先判断用户数量是否满了
    if (sys->userCount >= MAX_USER) {
        printf("用户数量已达上限，无法新增！\n");
        return;
    }

    User newUser;
    // 输入用户账号（学号）
    printf("请输入用户账号（学号）：");
    scanf("%s", newUser.userId);
    // 检查账号是否已存在
    if (findUserByUserId(sys, newUser.userId) != -1) {
        printf("该账号已存在，开户失败！\n");
        return;
    }

    // 初始密码设为123456（方便用户记住）
    strcpy(newUser.pwd, "123456");

    // 输入用户姓名
    printf("请输入用户姓名：");
    scanf("%s", newUser.name);

    // 自动生成校园卡号（从100001开始递增）
    newUser.cardId = 100001 + sys->userCount;
    newUser.balance = 0.0f; // 初始余额0元
    newUser.status = 1;     // 初始状态正常

    // 把新用户添加到系统中
    sys->users[sys->userCount++] = newUser;
    printf("开户成功！\n");
    printf("用户账号：%s\n", newUser.userId);
    printf("校园卡号：%d\n", newUser.cardId);
    printf("初始密码：123456（提醒用户及时修改）\n");
}

// 校园卡充值
void rechargeCard(SystemData *sys) {
    int cardId;
    float amount;

    printf("请输入校园卡号：");
    scanf("%d", &cardId);
    // 找对应的用户
    int userIdx = findUserByCardId(sys, cardId);
    if (userIdx == -1) {
        printf("未找到该校园卡用户！\n");
        return;
    }

    User *user = &sys->users[userIdx];
    // 挂失的卡不能充值
    if (user->status == 0) {
        printf("该卡已挂失，无法充值！\n");
        return;
    }

    // 输入充值金额
    printf("请输入充值金额（必须大于0）：");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("充值金额无效！\n");
        return;
    }

    // 更新余额+保存交易记录
    user->balance += amount;
    saveTransRecord(sys, cardId, RECHARGE, amount);
    printf("充值成功！\n");
    printf("用户：%s\n", user->name);
    printf("原余额：%.2f 元\n", user->balance - amount);
    printf("充值金额：%.2f 元\n", amount);
    printf("当前余额：%.2f 元\n", user->balance);
}

// 查询并修改用户信息
void queryAndModifyUser(SystemData *sys) {
    char userId[ID_LEN];
    printf("请输入要操作的用户账号（学号）：");
    scanf("%s", userId);
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("未找到该用户！\n");
        return;
    }

    User *user = &sys->users[userIdx];
    // 先显示当前信息
    printf("\n===== 当前用户信息 =====\n");
    printf("账号：%s\n", user->userId);
    printf("姓名：%s\n", user->name);
    printf("校园卡号：%d\n", user->cardId);
    printf("余额：%.2f 元\n", user->balance);
    printf("状态：%s\n", user->status == 1 ? "正常" : "挂失");
    printf("========================\n");

    // 选择是否修改
    printf("是否修改用户姓名？（1=是，0=否）：");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("请输入新姓名：");
        scanf("%s", user->name);
        printf("姓名修改成功！\n");
    } else {
        printf("已取消修改！\n");
    }
}

// 重置用户密码（改为123456）
void resetUserPwd(SystemData *sys) {
    char userId[ID_LEN];
    printf("请输入要重置密码的用户账号（学号）：");
    scanf("%s", userId);
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("未找到该用户！\n");
        return;
    }

    // 直接重置为123456
    strcpy(sys->users[userIdx].pwd, "123456");
    printf("密码重置成功！新密码：123456（提醒用户及时修改）\n");
}

// 管理员直接修改用户密码
void modifyUserPwdByAdmin(SystemData *sys) {
    char userId[ID_LEN];
    char newPwd[PWD_LEN];
    printf("请输入要修改密码的用户账号（学号）：");
    scanf("%s", userId);
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("未找到该用户！\n");
        return;
    }

    // 输入新密码
    printf("请输入新密码：");
    scanf("%s", newPwd);
    strcpy(sys->users[userIdx].pwd, newPwd);
    printf("密码修改成功！新密码已生效！\n");
}

// 管理员帮用户挂失/解挂
void toggleUserCardStatusByAdmin(SystemData *sys) {
    char userId[ID_LEN];
    printf("请输入要操作的用户账号（学号）：");
    scanf("%s", userId);
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("未找到该用户！\n");
        return;
    }

    User *user = &sys->users[userIdx];
    if (user->status == 1) {
        user->status = 0;
        printf("挂失成功！该卡已冻结！\n");
    } else {
        user->status = 1;
        printf("解挂成功！该卡已恢复正常！\n");
    }
}

// 注销校园卡（删除用户）
void cancelUserAccount(SystemData *sys) {
    char userId[ID_LEN];
    printf("请输入要注销的用户账号（学号）：");
    scanf("%s", userId);
    int userIdx = findUserByUserId(sys, userId);
    if (userIdx == -1) {
        printf("未找到该用户！\n");
        return;
    }

    User *user = &sys->users[userIdx];
    // 确认是否注销
    printf("确定要注销用户【%s（账号：%s）】吗？（y=是，n=否）：", user->name, userId);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("已取消注销！\n");
        return;
    }

    //  删除用户：后面的用户往前移一位
    for (int i = userIdx; i < sys->userCount - 1; i++) {
        sys->users[i] = sys->users[i + 1];
    }
    sys->userCount--; // 用户数-1
    printf("注销成功！该用户所有信息已删除！\n");
}
