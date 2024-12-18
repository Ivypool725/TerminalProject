#include "FileUploadController.h"
#include <sstream>

// 处理文件上传逻辑，从网络请求解析获取文件名和文件内容并上传
void FileUploadController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto fileNameIt = params.find("filename");
    auto fileContentIt = params.find("filecontent");
    if (fileNameIt != params.end() && fileContentIt != params.end()) {
        if (model.currentUser.empty()) {
            std::string response = "请先登录再执行文件上传操作";
            send(clientSocket, response.c_str(), response.length(), 0);
            return;
        }
        model.addFile(fileNameIt->second, fileContentIt->second);
        std::string response = "文件上传成功";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    else {
        std::string response = "请求参数中缺少文件名或文件内容";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
}
