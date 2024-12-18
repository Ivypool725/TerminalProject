#include "CloudStorageController.h"

// ���캯����ʼ��������
CloudStorageController::CloudStorageController() {}

// ���г����߼����ȴ����¼���ٽ������˵�����ѭ��
void CloudStorageController::run() {
    while (true) {
        view.showMainMenu();
        std::string input = view.getUserInput();
        if (input == "1") {
            FileUploadController uploadController(model, view);
            uploadController.handle();
        }
        else if (input == "2") {
            FileDownloadController downloadController(model, view);
            downloadController.handle();
        }
        else if (input == "3") {
            const auto& files = model.getCurrentUserFiles();
            view.showFiles(files);
        }
        else if (input == "4") {
            LoginController loginController(model, view);
            loginController.handle();
        }
        else if (input == "5") {
            LogoutController logoutController(model, view);
            logoutController.handle();
        }
        else if (input == "6") {
            OtherUsersFilesViewerController otherUsersFilesController(model, view);
            otherUsersFilesController.handle();
        }
        else if (input == "7") {
            view.showMessage("�˳��ƶ˴洢����");
            break;
        }
        else {
            view.showMessage("��Ч�����룬���������롣");
        }
    }
}
