#pragma once
#include "CloudStorageModel.h"
#include<Windows.h>

// ���캯������ʼ�������ļ�·�������Լ�����������
CloudStorageModel::CloudStorageModel(const std::string& filePath) : dataFilePath(filePath) {
    loadDataFromFile();
}

// ���ļ������û����ݵ�˽�к���
void CloudStorageModel::loadDataFromFile() {
    std::ifstream file(dataFilePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string username, password;
            std::getline(iss, username, ',');
            std::getline(iss, password, ',');
            // ��ʾ�����������ÿ�и�ʽΪ "username,password,file1:content1;file2:content2..."
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

// ���û����ݱ��浽�ļ���˽�к���
void CloudStorageModel::saveDataToFile() const {
    std::ofstream file(dataFilePath);
    if (file.is_open()) {
        for (const auto& outerPair : allUsersFiles) {
            std::string line = outerPair.first + ",";
            // ��ʾ���������������ͳһ�洢Ϊ�̶�ֵ��ʵ��Ӧ������ʵ����洢���ƣ�
            line += "password,";
            for (const auto& innerPair : outerPair.second) {
                line += innerPair.first + ":" + innerPair.second + ";";
            }
            line.pop_back();  // �Ƴ�������ķֺ�
            file << line << "\n";
        }
        file.close();
    }
}

// �û���֤����
bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
    auto it = allUsersFiles.find(username);
    if (it != allUsersFiles.end()) {
        // ��ʾ���������������ͳһ�洢Ϊ�̶�ֵ��ʵ��Ӧ������ʵ����洢���ƣ�
        if (password == "password") {
            return true;
        }
    }
    return false;
}
// �û���֤������ʹ�������ϣ������֤�û�
//bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
//    auto it = allUsersFiles.find(username);
//    if (it != allUsersFiles.end()) {
//        // ��ȡ�洢�Ĺ�ϣ����
//        const std::string& storedHash = it->second.find("password_hash")->second;
//
//        // ������������Ĺ�ϣֵ
//        unsigned char hash[SHA256_DIGEST_LENGTH];
//        EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
//        const EVP_MD* md = EVP_sha256();
//
//        EVP_DigestInit_ex(mdctx, md, NULL);
//        EVP_DigestUpdate(mdctx, password.c_str(), password.length());
//        EVP_DigestFinal_ex(mdctx, hash, NULL);
//        EVP_MD_CTX_free(mdctx);
//
//        // ������õ��Ĺ�ϣֵת��Ϊʮ�������ַ���������Ƚ�
//        char hex_chars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
//        std::string computedHashHex;
//        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//            computedHashHex += hex_chars[(hash[i] & 0xF0) >> 4];
//            computedHashHex += hex_chars[hash[i] & 0x0F];
//        }
//
//        // �Ƚϼ���õ��Ĺ�ϣֵ�ʹ洢�Ĺ�ϣֵ�Ƿ�һ��
//        return computedHashHex == storedHash;
//    }
//    return false;
//}


// ���õ�ǰ�û�
void CloudStorageModel::setCurrentUser(const std::string& user) {
    currentUser = user;
}

// ����ļ���������ӵ���ǰ��¼�û����ļ��б��У�
void CloudStorageModel::addFile(const std::string& fileName, const std::string& fileContent) {
    if (currentUser.empty()) {
        std::cerr << "���ȵ�¼��ִ�в���" << std::endl;
        return;
    }
    allUsersFiles[currentUser][fileName] = fileContent;
    saveDataToFile();  // �������ݵ��ļ���ȷ�����ݳ־û�
}

// �Ƴ���ǰ��¼�û���ָ���ļ�
void CloudStorageModel::removeFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "���ȵ�¼��ִ�в���" << std::endl;
        return;
    }
    allUsersFiles[currentUser].erase(fileName);
    saveDataToFile();  // �������ݵ��ļ���ȷ�����ݳ־û�
}

// ��ȡ��ǰ��¼�û����ļ��б�
const std::unordered_map<std::string, std::string>& CloudStorageModel::getCurrentUserFiles() const {
    return allUsersFiles.at(currentUser);
}

// ���ص�ǰ��¼�û����ļ�
std::string CloudStorageModel::downloadFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "���ȵ�¼��ִ�в���" << std::endl;
        return "";
    }
    auto it = allUsersFiles[currentUser].find(fileName);
    if (it != allUsersFiles[currentUser].end()) {
        return it->second;
    }
    return "";
}

// �ǳ�ʱ�����ǰ�û��������
void CloudStorageModel::clearCurrentUser() {
    currentUser = "";
}

// ��ȡ�����û��ļ���Ϣ������ת�����ݽṹ����չʾ��
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

// ���������û��ļ������������������ƵĴ�������߼�
std::string CloudStorageModel::downloadOtherUserFile(const std::string& otherUserName, const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "���ȵ�¼��ִ�в���" << std::endl;
        return "";
    }
    if (!authenticateUser(currentUser, "")) {  // ���жϵ�ǰ�û��Ƿ�Ϸ���¼��ʵ�ʿ��ܸ�������֤
        std::cerr << "��û��Ȩ�����������û��ļ���" << std::endl;
        return "";
    }
    auto userIt = allUsersFiles.find(otherUserName);
    if (userIt == allUsersFiles.end()) {
        std::cerr << "ָ���������û������ڡ�" << std::endl;
        return "";
    }
    auto fileIt = userIt->second.find(fileName);
    if (fileIt == userIt->second.end()) {
        std::cerr << "ָ���������û��ļ������ڡ�" << std::endl;
        return "";
    }
    return fileIt->second;
}
