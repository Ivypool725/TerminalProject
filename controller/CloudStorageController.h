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
    void run();  // �������������߼����ڷ����������������������
};
