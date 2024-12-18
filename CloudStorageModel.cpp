#include "CloudStorageModel.h"
#include <algorithm>

// �򵥵��û���Ϣ��ģ�����ݿ�洢��ʵ�ʻ������������ݿ⽻����
std::unordered_map<std::string, std::string> users = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

// ���캯����ʼ��
CloudStorageModel::CloudStorageModel() {}

// �û���֤����
bool CloudStorageModel::authenticateUser(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        return true;
    }
    return false;
}

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
}

// �Ƴ���ǰ��¼�û���ָ���ļ�
void CloudStorageModel::removeFile(const std::string& fileName) {
    if (currentUser.empty()) {
        std::cerr << "���ȵ�¼��ִ�в���" << std::endl;
        return;
    }
    allUsersFiles[currentUser].erase(fileName);
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
    //if (!authenticateUser(currentUser, "")) {  // ���жϵ�ǰ�û��Ƿ�Ϸ���¼��ʵ�ʿ��ܸ�������֤
    //    std::cerr << "��û��Ȩ�����������û��ļ���" << std::endl;
    //    return "";
    //}
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