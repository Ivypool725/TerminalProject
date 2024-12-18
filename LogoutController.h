#pragma once
#include "CloudStorageBaseController.h"

class LogoutController : public CloudStorageBaseController
{
public:
	LogoutController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {};
	void handle();
};