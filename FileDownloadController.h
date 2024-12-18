#pragma once
#include "CloudStorageBaseController.h"

class FileDownloadController : public CloudStorageBaseController {
public:
    FileDownloadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle();  // 实现父类纯虚函数，处理文件下载逻辑
};
