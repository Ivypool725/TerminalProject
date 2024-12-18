#pragma once
#include "CloudStorageModel.h"
#include<Windows.h>

// 构造函数，初始化数据文件路径并尝试加载已有数据
CloudStorageModel::CloudStorageModel(const std::string& filePath) : dataFilePath(filePath) {
    loadDataFromFile();
}

// 从文件加载用户数据的私有函数
void CloudStorageModel::loadDataFromFile() {
    std::ifstream file(dataFilePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password;
            std::getline(iss, username, ',');
            std::getline(iss, password, ',');
            // 简单示例，这里假设每行格式为 "username,password,file1:content1;file2:content2..."
            std::string fileInfo;
            std::getline(iss, fileInfo);
            std::unordered_map<std::string, std::string> userFiles;
            if (!fileInfo.empty()) {
                std::istringstream fileIss(fileInfo);
                std::string filePair;
                while (std::getline(fileIss, filePair, ';')) {
                    std::istringstream pairIss(filePair);
                    std::string fileName, fileContent;
                    std::getline(pairIss, fileName, ':');
                    std::getline(pairIss, fileContent);
                    userFiles[fileName] = fileContent;
                }
            }
            allUsersFiles[username] = userFiles;
        }
        file.close();
    }
}

// 将用户数据保存到文件的私有函数
void CloudStorageModel::saveDataToFile() const {
    std::ofstream file(dataFilePath);
    if (file.is_open()) {
        for (const auto& outerPair : allUsersFiles) {
            std::string line = outerPair.first + ",";
            // 简单示例，这里假设密码统一存储为固定值（实际应用需真实密码存储机制）
            line += "password,";
            for (const auto& innerPair : outerPair.second) {
                line += innerPair.first + ":" + innerPair.second + ";";
            }
            line.pop_back();  // 移除最后多余的分号
            file << line << "\n";
        }
        file.close();
    }
}

// 用户认证方法
bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
    auto it = allUsersFiles.find(username);
    if (it != allUsersFiles.end()) {
        // 简单示例，这里假设密码统一存储为固定值（实际应用需真实密码存储机制）
        if (password == "password") {
            return true;
        }
    }
    return false;
}
// 用户认证方法，使用密码哈希机制验证用户
//bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
//    auto it = allUsersFiles.find(username);
//    if (it != allUsersFiles.end()) {
//        // 获取存储的哈希密码
//        const std::string& storedHash = it->second.find("password_hash")->second;
//
//        // 计算输入密码的哈希值
//        unsigned char hash[SHA256_DIGEST_LENGTH];
//        EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
//        const EVP_MD* md = EVP_sha256();
//
//        EVP_DigestInit_ex(mdctx, md, NULL);
//        EVP_DigestUpdate(mdctx, password.c_str(), password.length());
//        EVP_DigestFinal_ex(mdctx, hash, NULL);
//        EVP_MD_CTX_free(mdctx);
//
//        // 将计算得到的哈希值转换为十六进制字符串，方便比较
//        char hex_chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
//        std::string computedHashHex;
//        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//            computedHashHex += hex_chars[(hash[i] & 0xF0) >> 4];
//            computedHashHex += hex_chars[hash[i] & 0x0F];
//        }
//
//        // 比较计算得到的哈希值和存储的哈希值是否一致
//        return computedHashHex == storedHash;
//    }
//    return false;
//}


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
    saveDataToFile();  // 保存数据到文件，确保数据持久化
}

// 移除当前登录用户的指定文件
void CloudStorageModel::removeFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "请先登录再执行操作" << std::endl;
        return;
    }
    allUsersFiles[currentUser].erase(fileName);
    saveDataToFile();  // 保存数据到文件，确保数据持久化
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
    if (!authenticateUser(currentUser, "")) {  // 简单判断当前用户是否合法登录，实际可能更复杂验证
        std::cerr << "您没有权限下载其他用户文件。" << std::endl;
        return "";
    }
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
