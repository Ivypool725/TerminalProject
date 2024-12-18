#include "CloudStorageView.h"
#include <sstream>

// 展示消息，按照HTTP协议规范构建响应消息并通过网络发送给客户端
void CloudStorageView::showMessage(const std::string& message, int clientSocket) {
    std::string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Content-Type: text/plain; charset=UTF-8\r\n";
    httpResponse += "Content-Length: " + std::to_string(message.length()) + "\r\n";
    httpResponse += "\r\n";
    httpResponse += message;

    send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
}

// 获取用户输入，当前简单实现，实际在网页端可通过解析请求参数替代
std::string CloudStorageView::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
