#include "LoginController.h"
#include <sstream>

// �����¼�߼�����������������û��������������֤��¼
void LoginController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto usernameIt = params.find("username");
    auto passwordIt = params.find("password");
    if (usernameIt != params.end() && passwordIt != params.end()) {
        bool isAuthenticated = model.authenticateUser(usernameIt->second, passwordIt->second);
        if (isAuthenticated) {
            model.setCurrentUser(usernameIt->second);
            std::string response = "��¼�ɹ�";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        else {
            std::string response = "�û������������";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
    }
    else {
        std::string response = "���������ȱ���û���������";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
