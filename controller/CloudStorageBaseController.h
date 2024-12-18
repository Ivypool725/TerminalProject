#pragma once
#include "../Model/CloudStorageModel.h"
#include "../View/CloudStorageView.h"

class CloudStorageBaseController {
protected:
    CloudStorageModel& model;
    CloudStorageView& view;

public:
    CloudStorageBaseController(CloudStorageModel& m, CloudStorageView& v) : model(m), view(v) {}
    virtual ~CloudStorageBaseController() {}
    virtual void handle(int clientSocket, const std::string& requestMethod, const std::string& requestPath, const std::unordered_map<std::string, std::string>& params) = 0;
};
