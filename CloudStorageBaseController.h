#pragma once

#include "CloudStorageModel.h"
#include "CloudStorageView.h"

class CloudStorageBaseController {
//private:
    
protected:
    CloudStorageModel& model;//是否加&
    CloudStorageView& view;

public:
    CloudStorageBaseController(CloudStorageModel& m, CloudStorageView& v) :model(m), view(v) {};
    virtual ~CloudStorageBaseController() {};
    virtual void handle() = 0;  // 纯虚函数，让子类实现具体业务处理逻辑
};



