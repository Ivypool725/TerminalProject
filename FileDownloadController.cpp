#include "FileDownloadController.h"

// �����ļ������߼�
void FileDownloadController::handle() {
    std::cout << "������Ҫ���ص��ļ�����";
    std::string fileName = view.getUserInput();
    std::string fileContent = model.downloadFile(fileName);
    if (!fileContent.empty()) {
        std::cout << "�ļ����ݣ�" << fileContent << std::endl;
    }
    else {
        view.showMessage("�ļ�������");
    }
}
