#pragma once
#include "CloudStorageBaseController.h"

class OtherUsersFilesViewerController : public CloudStorageBaseController {
private:
    std::string selectedOtherUserName;
    std::vector<std::pair<std::string, std::vector<std::string>>> otherUsersFiles;
public:
    OtherUsersFilesViewerController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle() override;  // 实现父类纯虚函数，处理查看其他用户文件逻辑
    void handleDownload();  // 处理下载文件逻辑
};
