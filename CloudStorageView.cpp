#include "CloudStorageView.h"

// 展示登录菜单
void CloudStorageView::showLoginMenu() {
    std::cout << "云端存储登录" << std::endl;
    std::cout << "用户名: ";
}

// 展示主操作菜单
void CloudStorageView::showMainMenu() {
    std::cout << "云端存储操作菜单：" << std::endl;
    std::cout << "1. 上传文件" << std::endl;
    std::cout << "2. 下载文件" << std::endl;
    std::cout << "3. 查看自己的文件列表" << std::endl;
    std::cout << "4. 登录" << std::endl;
    std::cout << "5. 登出" << std::endl;
    std::cout << "6. 查看其他用户文件" << std::endl;
    std::cout << "7. 退出" << std::endl;
}

// 展示文件列表
void CloudStorageView::showFiles(const std::unordered_map<std::string, std::string>& files) {
    std::cout << "云端存储中的文件列表：" << std::endl;
    for (const auto& pair : files) {
        std::cout << "- " << pair.first << std::endl;
    }
}

// 展示其他用户文件列表（新格式），可根据参数决定是否显示下载选项
void CloudStorageView::showOtherUsersFiles(const std::vector<std::pair<std::string, std::vector<std::string>>>& files, bool showDownloadOption) {
    std::cout << "其他用户的文件列表：" << std::endl;
    for (const auto& userFilesPair : files) {
        std::cout << "用户: " << userFilesPair.first << std::endl;
        for (const auto& fileName : userFilesPair.second) {
            std::cout << "  - " << fileName << std::endl;
        }
    }
    if (showDownloadOption) {
        std::cout << "输入要下载文件对应的用户名和文件名（以空格分隔），输入0返回主菜单：";
    }
}

// 获取用户输入
std::string CloudStorageView::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// 展示消息
void CloudStorageView::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}
