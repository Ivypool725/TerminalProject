#pragma once
#include "CloudStorageBaseController.h"
#include<Windows.h>

class FileDownloadController : public CloudStorageBaseController {
public:
    FileDownloadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) ;  // ʵ�ָ��ി�麯���������ļ������߼��������������ȡ�ļ����������ļ����ݸ��ͻ���
};
