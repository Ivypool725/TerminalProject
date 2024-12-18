#pragma once
#include "OtherUsersFilesViewerController.h"
#include<sstream>

// ����鿴�����û��ļ��߼�
void OtherUsersFilesViewerController::handle() {
    otherUsersFiles = model.getOtherUsersFiles();
    view.showOtherUsersFiles(otherUsersFiles, true);
    std::string input = view.getUserInput();
    if (input == "0") {
        return;
    }
    std::stringstream ss(input);
    std::string otherUserName;
    std::string fileName;
    if (ss >> otherUserName >> fileName) {
        std::string fileContent = model.downloadOtherUserFile(otherUserName, fileName);
        if (!fileContent.empty()) {
            // ������Ը���ʵ����������ص��ļ����ݽ�һ���������籣�浽���صȣ���ǰʾ��ֻ�Ǽ����
            std::cout << "�ɹ����������û��ļ����ļ��������£�" << std::endl << fileContent << std::endl;
        }
        else {
            view.showMessage("ָ���������û��ļ������ڡ�");
        }
    }
    else {
        view.showMessage("�����ʽ���������������û������ļ������Կո�ָ�����");
        handle();
    }
}

// ���������ļ��߼�
void OtherUsersFilesViewerController::handleDownload() {
    handle();
}
