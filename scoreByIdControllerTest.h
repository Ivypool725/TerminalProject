#pragma once
#include "controllertest.h"


class ScoreByIdController : public Controller
{
public:

	ModelAndView modelAndView;
	void setTemplateName_C();
	void addTableData_C(int);
	void scoreByIdContHandle(SOCKET sockClient, string Para);//°ó¶¨Õâ¸ö
};