#include "CloudStorageView.h"

// չʾ��¼�˵�
void CloudStorageView::showLoginMenu() {
    std::cout << "�ƶ˴洢��¼" << std::endl;
    std::cout << "�û���: ";
}

// չʾ�������˵�
void CloudStorageView::showMainMenu() {
    std::cout << "�ƶ˴洢�����˵���" << std::endl;
    std::cout << "1. �ϴ��ļ�" << std::endl;
    std::cout << "2. �����ļ�" << std::endl;
    std::cout << "3. �鿴�Լ����ļ��б�" << std::endl;
    std::cout << "4. ��¼" << std::endl;
    std::cout << "5. �ǳ�" << std::endl;
    std::cout << "6. �鿴�����û��ļ�" << std::endl;
    std::cout << "7. �˳�" << std::endl;
}

// չʾ�ļ��б�
void CloudStorageView::showFiles(const std::unordered_map<std::string, std::string>& files) {
    std::cout << "�ƶ˴洢�е��ļ��б�" << std::endl;
    for (const auto& pair : files) {
        std::cout << "- " << pair.first << std::endl;
    }
}

// չʾ�����û��ļ��б��¸�ʽ�����ɸ��ݲ��������Ƿ���ʾ����ѡ��
void CloudStorageView::showOtherUsersFiles(const std::vector<std::pair<std::string, std::vector<std::string>>>& files, bool showDownloadOption) {
    std::cout << "�����û����ļ��б�" << std::endl;
    for (const auto& userFilesPair : files) {
        std::cout << "�û�: " << userFilesPair.first << std::endl;
        for (const auto& fileName : userFilesPair.second) {
            std::cout << "  - " << fileName << std::endl;
        }
    }
    if (showDownloadOption) {
        std::cout << "����Ҫ�����ļ���Ӧ���û������ļ������Կո�ָ���������0�������˵���";
    }
}

// ��ȡ�û�����
std::string CloudStorageView::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// չʾ��Ϣ
void CloudStorageView::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}
