#pragma once

#include "CloudStorageModel.h"
#include "CloudStorageView.h"

class CloudStorageBaseController {
//private:
    
protected:
    CloudStorageModel& model;//�Ƿ��&
    CloudStorageView& view;

public:
    CloudStorageBaseController(CloudStorageModel& m, CloudStorageView& v) :model(m), view(v) {};
    virtual ~CloudStorageBaseController() {};
    virtual void handle() = 0;  // ���麯����������ʵ�־���ҵ�����߼�
};



