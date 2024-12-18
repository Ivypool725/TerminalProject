#include "CloudStorageView.h"
#include <sstream>

// չʾ��Ϣ������HTTPЭ��淶������Ӧ��Ϣ��ͨ�����緢�͸��ͻ���
void CloudStorageView::showMessage(const std::string& message, int clientSocket) {
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: text/plain; charset=UTF-8\r\n";
    httpResponse += "Content-Length: " + std::to_string(message.length()) + "\r\n";
    httpResponse += "\r\n";
    httpResponse += message;

    send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
}

// ��ȡ�û����룬��ǰ��ʵ�֣�ʵ������ҳ�˿�ͨ����������������
std::string CloudStorageView::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
