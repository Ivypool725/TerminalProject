#include "FileUploadController.h"
#include <sstream>

// �����ļ��ϴ��߼������������������ȡ�ļ������ļ����ݲ��ϴ�
void FileUploadController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto fileNameIt = params.find("filename");
    auto fileContentIt = params.find("filecontent");
    if (fileNameIt != params.end() && fileContentIt != params.end()) {
        if (model.currentUser.empty()) {
            std::string response = "���ȵ�¼��ִ���ļ��ϴ�����";
            send(clientSocket, response.c_str(), response.length(), 0);
            return;
        }
        model.addFile(fileNameIt->second, fileContentIt->second);
        std::string response = "�ļ��ϴ��ɹ�";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    else {
        std::string response = "���������ȱ���ļ������ļ�����";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
