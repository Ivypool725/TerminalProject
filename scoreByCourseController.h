#pragma once
#include "controllertest.h"


class ScoreByCourseController : public Controller
{
public:

	ModelAndView modelAndView;
	void setTemplateName_C();
	void addTableData_C(int);
	void scoreByCourseContHandle(SOCKET sockClient, string Para);//°ó¶¨Õâ¸ö
};