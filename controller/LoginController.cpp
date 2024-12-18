#include "LoginController.h"
#include <sstream>

// 处理登录逻辑，从网络请求解析用户名和密码进行验证登录
void LoginController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto usernameIt = params.find("username");
    auto passwordIt = params.find("password");
    if (usernameIt != params.end() && passwordIt != params.end()) {
        bool isAuthenticated = model.authenticateUser(usernameIt->second, passwordIt->second);
        if (isAuthenticated) {
            model.setCurrentUser(usernameIt->second);
            std::string response = "登录成功";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        else {
            std::string response = "用户名或密码错误";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
    }
    else {
        std::string response = "请求参数中缺少用户名或密码";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
