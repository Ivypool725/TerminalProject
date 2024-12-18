#pragma once
#include "CloudStorageBaseController.h"

class OtherUsersFilesViewerController : public CloudStorageBaseController {
public:
    OtherUsersFilesViewerController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params);  // 实现父类纯虚函数，处理查看其他用户文件逻辑，获取信息并返回给客户端展示
};
