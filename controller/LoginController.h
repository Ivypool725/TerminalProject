#pragma once
#include "CloudStorageBaseController.h"

class LoginController : public CloudStorageBaseController {
public:
    LoginController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) ;  // ʵ�ָ��ി�麯���������¼�߼��������������ȡ�û��������벢��֤��¼
};
