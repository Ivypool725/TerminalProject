#include "OtherUsersFilesViewerController.h"

// 处理查看其他用户文件逻辑，获取其他用户文件信息并返回给客户端
void OtherUsersFilesViewerController::handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) {
    auto otherUsersFiles = model.getOtherUsersFiles();
    std::string response = "其他用户文件信息如下：\n";
    for (const auto& userFilesPair : otherUsersFiles) {
        response += "用户: " + userFilesPair.first + "\n";
        for (const auto& fileName : userFilesPair.second) {
            response += "  - " + fileName + "\n";
        }
    }
    send(clientSocket, response.c_str(), response.length(), 0);
}
