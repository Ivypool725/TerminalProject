#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

class CloudStorageModel {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> allUsersFiles;  // ���û�����Ϊ�������洢ÿ���û����ļ����ڲ��Ϊ�ļ�����ֵΪ�ļ����ݣ�
   
    std::string dataFilePath;  // ���ڴ洢�û����ݵ��ļ�·����ģ�����ݿ�洢

    // ���ļ������û����ݵ�˽�к���
    void loadDataFromFile();
    // ���û����ݱ��浽�ļ���˽�к���
    void saveDataToFile() const;

public:

    std::string currentUser;  // ��ǰ��¼�û�


    CloudStorageModel(const std::string& filePath = "cloud_storage_data.txt");
    bool authenticateUser(const std::string& username, const std::string& password);  // �û���֤
    void setCurrentUser(const std::string& user);  // ���õ�ǰ�û�
    void addFile(const std::string& fileName, const std::string& fileContent);  // ����ļ�����ӵ���ǰ��¼�û����ļ��б��У�
    void removeFile(const std::string& fileName);  // �Ƴ���ǰ��¼�û���ָ���ļ�
    const std::unordered_map<std::string, std::string>& getCurrentUserFiles() const;  // ��ȡ��ǰ��¼�û����ļ��б�
    std::string downloadFile(const std::string& fileName);  // ���ص�ǰ��¼�û����ļ�
    void clearCurrentUser();  // �ǳ�ʱ�����ǰ�û��������
    std::vector<std::pair<std::string, std::vector<std::string>>> getOtherUsersFiles() const;  // ��ȡ�����û��ļ���Ϣ���Ը�����չʾ�ĸ�ʽ��
    std::string downloadOtherUserFile(const std::string& otherUserName, const std::string& fileName);  // ���������û��ļ��������ṩ�Ľӿں���
};
