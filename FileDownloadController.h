#pragma once
#include "CloudStorageBaseController.h"

class FileDownloadController : public CloudStorageBaseController {
public:
    FileDownloadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle();  // ʵ�ָ��ി�麯���������ļ������߼�
};
