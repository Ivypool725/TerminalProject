#pragma once
//#include<string>
#include "controllertest.h"


class StudentsController : public Controller
{
public:
	//չʾ����ѧ���ĸ�����Ϣ
	ModelAndView modelAndView;
	void setTemplateName_C();
	void addTableData_C();
	void stuContHandle(SOCKET, string);//�����

};