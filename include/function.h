#ifndef FUNCATION_H
#define FUNCATION_H

#include "struct.h"

// 系统工具函数
void initSystem(SystemData *sys);          // 初始化系统（加载测试数据）
int findUserByUserId(SystemData *sys, char *userId); // 按用户账号找用户（返回索引，没找到返回-1）
int findUserByCardId(SystemData *sys, int cardId);   // 按校园卡号找用户（返回索引）
int findCardAdminByAdminId(SystemData *sys, char *adminId); // 按管理员账号找管理员（返回索引）
void saveTransRecord(SystemData *sys, int cardId, TransType type, float amount); // 保存交易记录
void getCurrentTime(char *timeStr);        // 获取当前时间

// 登录功能函数
int userLogin(SystemData *sys, char *userId, char *pwd); // 校园卡用户登录（成功返回用户索引）
int cardAdminLogin(SystemData *sys, char *adminId, char *pwd); // 卡管理员登录（成功返回管理员索引）
int systemAdminLogin(char *adminId, char *pwd); // 系统管理员登录（成功返回1，失败返回0）

// 校园卡用户功能函数
void changeOwnPwd(SystemData *sys, int userIdx); // 修改自己的密码
void queryOwnBalance(SystemData *sys, int userIdx); // 查询自己的余额
void queryOwnConsumption(SystemData *sys, int userIdx); // 查询自己的消费记录
void toggleOwnCardStatus(SystemData *sys, int userIdx); // 挂失/解挂自己的卡

// 卡管理员功能函数
void createUser(SystemData *sys);          // 开户办理（新增校园卡用户）
void rechargeCard(SystemData *sys);        // 校园卡充值
void queryAndModifyUser(SystemData *sys);  // 查询并修改用户信息
void resetUserPwd(SystemData *sys);        // 重置用户密码（改为123456）
void modifyUserPwdByAdmin(SystemData *sys); // 管理员直接修改用户密码
void toggleUserCardStatusByAdmin(SystemData *sys); // 管理员帮用户挂失/解挂
void cancelUserAccount(SystemData *sys);   // 注销校园卡（删除用户）

// 系统管理员功能函数
void addCardAdmin(SystemData *sys);        // 新增卡管理员账号
void deleteCardAdmin(SystemData *sys);     // 删除卡管理员账号
void queryAllUsers(SystemData *sys);       // 查询所有用户信息
void queryAllCardAdmins(SystemData *sys);  // 查询所有卡管理员信息

#endif
