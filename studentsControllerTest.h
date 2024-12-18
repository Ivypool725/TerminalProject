#pragma once
//#include<string>
#include "controllertest.h"


class StudentsController : public Controller
{
public:
	//展示所有学生的个人信息
	ModelAndView modelAndView;
	void setTemplateName_C();
	void addTableData_C();
	void stuContHandle(SOCKET, string);//绑定这个

};