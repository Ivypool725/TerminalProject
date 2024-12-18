#pragma once
#include "CloudStorageBaseController.h"
#include<Windows.h>

class FileDownloadController : public CloudStorageBaseController {
public:
    FileDownloadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) ;  // 实现父类纯虚函数，处理文件下载逻辑，从网络请求获取文件名并返回文件内容给客户端
};
