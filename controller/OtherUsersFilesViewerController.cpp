#include "OtherUsersFilesViewerController.h"

// ����鿴�����û��ļ��߼�����ȡ�����û��ļ���Ϣ�����ظ��ͻ���
void OtherUsersFilesViewerController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto otherUsersFiles = model.getOtherUsersFiles();
    std::string response = "�����û��ļ���Ϣ���£�\n";
    for (const auto& userFilesPair : otherUsersFiles) {
        response += "�û�: " + userFilesPair.first + "\n";
        for (const auto& fileName : userFilesPair.second) {
            response += "  - " + fileName + "\n";
        }
    }
    send(clientSocket, response.c_str(), response.length(), 0);
}
