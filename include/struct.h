#ifndef STRUCT_H
#define STRUCT_H

// 常量定义（新手好记，直接用数字表示上限）
#define MAX_USER 100        // 最大校园卡用户数
#define MAX_CARD_ADMIN 20   // 最大卡管理员数
#define MAX_RECORD 1000     // 最大交易记录数
#define ID_LEN 12           // 账号长度（学号/管理员账号）
#define PWD_LEN 10          // 密码长度
#define NAME_LEN 20         // 姓名长度
#define TIME_LEN 20         // 时间字符串长度

// 交易类型枚举：0=消费，1=充值（用数字方便判断）
typedef enum {
    CONSUMPTION = 0,
    RECHARGE = 1
} TransType;

// 校园卡用户结构体
typedef struct {
    char userId[ID_LEN];    // 用户账号（比如学号）
    char pwd[PWD_LEN];      // 密码
    char name[NAME_LEN];    // 姓名
    int cardId;             // 校园卡号（唯一标识）
    float balance;          // 卡内余额
    int status;             // 卡状态：1=正常，0=挂失
} User;

// 卡管理员结构体
typedef struct {
    char adminId[ID_LEN];   // 管理员账号
    char pwd[PWD_LEN];      // 密码
    char name[NAME_LEN];    // 姓名
} CardAdmin;

// 交易记录结构体（存储消费/充值记录）
typedef struct {
    int cardId;             // 关联的校园卡号
    TransType type;         // 交易类型（消费/充值）
    float amount;           // 交易金额
    char time[TIME_LEN];    // 交易时间（格式：年-月-日 时:分:秒）
} TransRecord;

// 系统全局数据（存储所有用户、管理员、交易记录）
typedef struct {
    User users[MAX_USER];           // 校园卡用户数组
    int userCount;                  // 当前用户总数
    CardAdmin cardAdmins[MAX_CARD_ADMIN]; // 卡管理员数组
    int cardAdminCount;             // 当前卡管理员总数
    TransRecord records[MAX_RECORD]; // 交易记录数组
    int recordCount;                // 当前交易记录总数
} SystemData;

// 单个学生结构体（与校园卡系统的 User 区分开）
typedef struct {
    char name[NAME_LEN];   // 姓名
    int id;                // 学号
    float score;           // 成绩
    int cardId;            // 学生卡号
    float balance;         // 余额
    int cardStatus;        // 卡状态：1=正常 0=挂失
} ST;

// 学生数组结构体（封装学生列表及当前数量）
typedef struct {
    ST students[MAX_USER]; // 学生数组
    int size;              // 当前学生数量
} STS;
// ================================================================================

#endif
