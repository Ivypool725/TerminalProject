#include "FileDownloadController.h"
#include <sstream>


// �����ļ������߼��������������ȡ�ļ����������ļ����ݷ��ظ��ͻ���
void FileDownloadController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto fileNameIt = params.find("filename");
    if (fileNameIt != params.end()) {
        if (model.currentUser.empty()) {
            std::string response = "���ȵ�¼��ִ���ļ����ز���";
            send(clientSocket, response.c_str(), response.length(), 0);
            return;
        }
        std::string fileContent = model.downloadFile(fileNameIt->second);
        if (!fileContent.empty()) {
            std::string response = "�ļ����سɹ����������£�\n" + fileContent;
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        else {
            std::string response = "�ļ�������";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
    }
    else {
        std::string response = "���������ȱ���ļ���";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
