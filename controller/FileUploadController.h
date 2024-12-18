#pragma once
#include "CloudStorageBaseController.h"

class FileUploadController : public CloudStorageBaseController {
public:
    FileUploadController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {}
    void handle(int clientSocket, const std::unordered_map<std::string, std::string>& params) override;
};
