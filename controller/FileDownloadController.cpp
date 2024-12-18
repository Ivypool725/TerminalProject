#include "FileDownloadController.h"
#include <sstream>


// 处理文件下载逻辑，从网络请求获取文件名并下载文件内容返回给客户端
void FileDownloadController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto fileNameIt = params.find("filename");
    if (fileNameIt != params.end()) {
        if (model.currentUser.empty()) {
            std::string response = "请先登录再执行文件下载操作";
            send(clientSocket, response.c_str(), response.length(), 0);
            return;
        }
        std::string fileContent = model.downloadFile(fileNameIt->second);
        if (!fileContent.empty()) {
            std::string response = "文件下载成功，内容如下：\n" + fileContent;
            send(clientSocket, response.c_str(), response.length(), 0);
        }
        else {
            std::string response = "文件不存在";
            send(clientSocket, response.c_str(), response.length(), 0);
        }
    }
    else {
        std::string response = "请求参数中缺少文件名";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
