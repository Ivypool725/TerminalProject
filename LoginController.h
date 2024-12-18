#pragma once
#include "CloudStorageBaseController.h"

class LoginController : public CloudStorageBaseController
{
public:
	LoginController(CloudStorageModel& m, CloudStorageView& v) : CloudStorageBaseController(m, v) {};
	void handle();
};