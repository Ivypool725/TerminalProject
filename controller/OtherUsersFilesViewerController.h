#pragma once
#include "CloudStorageBaseController.h"

class OtherUsersFilesViewerController : public CloudStorageBaseController {
public:
    OtherUsersFilesViewerController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params);  // ʵ�ָ��ി�麯��������鿴�����û��ļ��߼�����ȡ��Ϣ�����ظ��ͻ���չʾ
};
