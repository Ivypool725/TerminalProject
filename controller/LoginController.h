#pragma once
#include "CloudStorageBaseController.h"

class LoginController : public CloudStorageBaseController {
public:
    LoginController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) ;  // 实现父类纯虚函数，处理登录逻辑，从网络请求获取用户名和密码并验证登录
};
