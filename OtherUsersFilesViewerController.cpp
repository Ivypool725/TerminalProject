#pragma once
#include "OtherUsersFilesViewerController.h"
#include<sstream>

// 处理查看其他用户文件逻辑
void OtherUsersFilesViewerController::handle() {
    otherUsersFiles = model.getOtherUsersFiles();
    view.showOtherUsersFiles(otherUsersFiles, true);
    std::string input = view.getUserInput();
    if (input == "0") {
        return;
    }
    std::stringstream ss(input);
    std::string otherUserName;
    std::string fileName;
    if (ss >> otherUserName >> fileName) {
        std::string fileContent = model.downloadOtherUserFile(otherUserName, fileName);
        if (!fileContent.empty()) {
            // 这里可以根据实际需求对下载的文件内容进一步处理，比如保存到本地等，当前示例只是简单输出
            std::cout << "成功下载其他用户文件，文件内容如下：" << std::endl << fileContent << std::endl;
        }
        else {
            view.showMessage("指定的其他用户文件不存在。");
        }
    }
    else {
        view.showMessage("输入格式错误，请重新输入用户名和文件名（以空格分隔）。");
        handle();
    }
}

// 处理下载文件逻辑
void OtherUsersFilesViewerController::handleDownload() {
    handle();
}
