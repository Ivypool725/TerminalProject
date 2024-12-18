#pragma once
#include "CloudStorageBaseController.h"

class LogoutController : public CloudStorageBaseController {
public:
    LogoutController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) override;  // ʵ�ָ��ി�麯��������ǳ��߼��������ǰ�û�������ò�������ʾ��Ϣ���ͻ���
};
