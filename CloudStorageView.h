#pragma once
#include<unordered_map>
#include <iostream>
#include <string>

class CloudStorageView {
public:
    void showLoginMenu();  // չʾ��¼�˵�
    void showMainMenu();  // չʾ�������˵�
    void showFiles(const std::unordered_map<std::string, std::string>& files);  // չʾ�ļ��б�
    void showOtherUsersFiles(const std::vector<std::pair<std::string, std::vector<std::string>>>& files, bool showDownloadOption = false);  // չʾ�����û��ļ��б��¸�ʽ��
    //void showOtherUsersFiles(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& files);  // չʾ�����û��ļ��б�
    std::string getUserInput();  // ��ȡ�û�����
    void showMessage(const std::string& message);  // չʾ��Ϣ
   
};
