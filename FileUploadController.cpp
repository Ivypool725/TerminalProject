#include "FileUploadController.h"

// �����ļ��ϴ��߼�
void FileUploadController::handle() {
    std::cout << "�������ļ�����";
    std::string fileName = view.getUserInput();
    std::cout << "�������ļ����ݣ�";
    std::string fileContent = view.getUserInput();
    model.addFile(fileName, fileContent);
    view.showMessage("�ļ��ϴ��ɹ�");
}
