#pragma once
#include "CloudStorageBaseController.h"

class FileUploadController : public CloudStorageBaseController {
public:
    FileUploadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle() ;  // ʵ�ָ��ി�麯���������ļ��ϴ��߼�
};
