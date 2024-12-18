#include "FileUploadController.h"

// 处理文件上传逻辑
void FileUploadController::handle() {
    std::cout << "请输入文件名：";
    std::string fileName = view.getUserInput();
    std::cout << "请输入文件内容：";
    std::string fileContent = view.getUserInput();
    model.addFile(fileName, fileContent);
    view.showMessage("文件上传成功");
}
