#include "CloudStorageController.h"

// 构造函数初始化控制器
CloudStorageController::CloudStorageController() {}

// 运行程序逻辑，先处理登录，再进入主菜单操作循环
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
            view.showMessage("退出云端存储程序。");
            break;
        }
        else {
            view.showMessage("无效的输入，请重新输入。");
        }
    }
}
