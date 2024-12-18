#include "FileDownloadController.h"

// 处理文件下载逻辑
void FileDownloadController::handle() {
    std::cout << "请输入要下载的文件名：";
    std::string fileName = view.getUserInput();
    std::string fileContent = model.downloadFile(fileName);
    if (!fileContent.empty()) {
        std::cout << "文件内容：" << fileContent << std::endl;
    }
    else {
        view.showMessage("文件不存在");
    }
}
