#pragma once
#include<unordered_map>
#include <iostream>
#include <string>

class CloudStorageView {
public:
    void showLoginMenu();  // 展示登录菜单
    void showMainMenu();  // 展示主操作菜单
    void showFiles(const std::unordered_map<std::string, std::string>& files);  // 展示文件列表
    void showOtherUsersFiles(const std::vector<std::pair<std::string, std::vector<std::string>>>& files, bool showDownloadOption = false);  // 展示其他用户文件列表（新格式）
    //void showOtherUsersFiles(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& files);  // 展示其他用户文件列表
    std::string getUserInput();  // 获取用户输入
    void showMessage(const std::string& message);  // 展示消息
   
};
