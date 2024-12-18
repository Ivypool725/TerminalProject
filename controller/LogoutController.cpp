#include "LogoutController.h"

// 处理登出逻辑，清除当前用户相关设置并返回登出成功提示给客户端
void LogoutController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    model.clearCurrentUser();
    std::string response = "登出成功";
    send(clientSocket, response.c_str(), response.length(), 0);
}
