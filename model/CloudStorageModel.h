#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class CloudStorageModel {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> allUsersFiles;  // 以用户名作为外层键，存储每个用户的文件（内层键为文件名，值为文件内容）
   
    std::string dataFilePath;  // 用于存储用户数据的文件路径，模拟数据库存储

    // 从文件加载用户数据的私有函数
    void loadDataFromFile();
    // 将用户数据保存到文件的私有函数
    void saveDataToFile() const;

public:

    std::string currentUser;  // 当前登录用户


    CloudStorageModel(const std::string& filePath = "cloud_storage_data.txt");
    bool authenticateUser(const std::string& username, const std::string& password);  // 用户认证
    void setCurrentUser(const std::string& user);  // 设置当前用户
    void addFile(const std::string& fileName, const std::string& fileContent);  // 添加文件（添加到当前登录用户的文件列表中）
    void removeFile(const std::string& fileName);  // 移除当前登录用户的指定文件
    const std::unordered_map<std::string, std::string>& getCurrentUserFiles() const;  // 获取当前登录用户的文件列表
    std::string downloadFile(const std::string& fileName);  // 下载当前登录用户的文件
    void clearCurrentUser();  // 登出时清除当前用户相关设置
    std::vector<std::pair<std::string, std::vector<std::string>>> getOtherUsersFiles() const;  // 获取其他用户文件信息（以更方便展示的格式）
    std::string downloadOtherUserFile(const std::string& otherUserName, const std::string& fileName);  // 下载其他用户文件，对外提供的接口函数
};
