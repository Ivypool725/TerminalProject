#pragma once
#include "CloudStorageBaseController.h"

class LogoutController : public CloudStorageBaseController {
public:
    LogoutController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) override;  // 实现父类纯虚函数，处理登出逻辑，清除当前用户相关设置并返回提示信息给客户端
};
