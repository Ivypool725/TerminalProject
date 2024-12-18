#pragma once
#include "controllertest.h"


class CoursesController : public Controller
{
public:
	
	ModelAndView modelAndView;
	void setTemplateName_C();
	void addTableData_C();
	void courseContHandle(SOCKET, string);//°ó¶¨Õâ¸ö
}; 