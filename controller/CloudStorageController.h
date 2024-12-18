#pragma once
#include "CloudStorageBaseController.h"
#include "FileUploadController.h"
#include "FileDownloadController.h"
#include "OtherUsersFilesViewerController.h"
#include "LoginController.h"
#include "LogoutController.h"

class CloudStorageController {
private:
    CloudStorageModel model;
    CloudStorageView view;

public:
    CloudStorageController();
    CloudStorageController(CloudStorageModel& m, CloudStorageView& v) : model(m), view(v) {}
    void run();  // 运行整个程序逻辑，在服务器启动后持续处理请求
};
