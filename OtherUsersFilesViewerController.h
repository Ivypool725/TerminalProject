#pragma once
#include "CloudStorageBaseController.h"

class OtherUsersFilesViewerController : public CloudStorageBaseController {
private:
    std::string selectedOtherUserName;
    std::vector<std::pair<std::string, std::vector<std::string>>> otherUsersFiles;
public:
    OtherUsersFilesViewerController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle() override;  // ʵ�ָ��ി�麯��������鿴�����û��ļ��߼�
    void handleDownload();  // ���������ļ��߼�
};
