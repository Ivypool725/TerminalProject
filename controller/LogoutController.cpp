#include "LogoutController.h"

// ����ǳ��߼��������ǰ�û�������ò����صǳ��ɹ���ʾ���ͻ���
void LogoutController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    model.clearCurrentUser();
    std::string response = "�ǳ��ɹ�";
    send(clientSocket, response.c_str(), response.length(), 0);
}
