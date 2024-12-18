#include "CloudStorageModel.h"
#include <algorithm>

// 简单的用户信息，模拟数据库存储（实际会是真正的数据库交互）
std::unordered_map<std::string, std::string> users = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

// 构造函数初始化
CloudStorageModel::CloudStorageModel() {}

// 用户认证方法
bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        return true;
    }
    return false;
}

// 设置当前用户
void CloudStorageModel::setCurrentUser(const std::string& user) {
    currentUser = user;
}

// 添加文件方法（添加到当前登录用户的文件列表中）
void CloudStorageModel::addFile(const std::string& fileName, const std::string& fileContent) {
    if (currentUser.empty()) {
        std::cerr << "请先登录再执行操作" << std::endl;
        return;
    }
    allUsersFiles[currentUser][fileName] = fileContent;
}

// 移除当前登录用户的指定文件
void CloudStorageModel::removeFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "请先登录再执行操作" << std::endl;
        return;
    }
    allUsersFiles[currentUser].erase(fileName);
}

// 获取当前登录用户的文件列表
const std::unordered_map<std::string, std::string>& CloudStorageModel::getCurrentUserFiles() const {
    return allUsersFiles.at(currentUser);
}

// 下载当前登录用户的文件
std::string CloudStorageModel::downloadFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "请先登录再执行操作" << std::endl;
        return "";
    }
    auto it = allUsersFiles[currentUser].find(fileName);
    if (it != allUsersFiles[currentUser].end()) {
        return it->second;
    }
    return "";
}

// 登出时清除当前用户相关设置
void CloudStorageModel::clearCurrentUser() {
    currentUser = "";
}

// 获取其他用户文件信息方法（转换数据结构方便展示）
std::vector<std::pair<std::string, std::vector<std::string>>> CloudStorageModel::getOtherUsersFiles() const {
    std::vector<std::pair<std::string, std::vector<std::string>>> result;
    for (const auto& outerPair : allUsersFiles) {
        if (outerPair.first != currentUser) {
            std::vector<std::string> fileNames;
            for (const auto& innerPair : outerPair.second) {
                fileNames.push_back(innerPair.first);
            }
            result.push_back(std::make_pair(outerPair.first, fileNames));
        }
    }
    return result;
}

// 下载其他用户文件方法，这里做更完善的错误处理等逻辑
std::string CloudStorageModel::downloadOtherUserFile(const std::string& otherUserName, const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "请先登录再执行操作" << std::endl;
        return "";
    }
    //if (!authenticateUser(currentUser, "")) {  // 简单判断当前用户是否合法登录，实际可能更复杂验证
    //    std::cerr << "您没有权限下载其他用户文件。" << std::endl;
    //    return "";
    //}
    auto userIt = allUsersFiles.find(otherUserName);
    if (userIt == allUsersFiles.end()) {
        std::cerr << "指定的其他用户不存在。" << std::endl;
        return "";
    }
    auto fileIt = userIt->second.find(fileName);
    if (fileIt == userIt->second.end()) {
        std::cerr << "指定的其他用户文件不存在。" << std::endl;
        return "";
    }
    return fileIt->second;
}