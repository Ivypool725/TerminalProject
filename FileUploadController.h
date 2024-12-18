#pragma once
#include "CloudStorageBaseController.h"

class FileUploadController : public CloudStorageBaseController {
public:
    FileUploadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle() ;  // 实现父类纯虚函数，处理文件上传逻辑
};
