#include "coursesControllerTest.h"


void CoursesController::setTemplateName_C()
{
	modelAndView.setTemplateName("courses.htm");
}
void CoursesController::addTableData_C()
{
	modelAndView.addTableData("courses-arr", "CourseService", -1);
}

void CoursesController::courseContHandle(SOCKET sockClient, string invalidPara)
{
	setTemplateName_C();

	addTableData_C();

	//const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
	const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";

	View view;
	string filledPage = view.replaceCourseTableData(&modelAndView);//change!!!!!!!!


	//string fullResponse = httpHeader + filledPage;
	string fullResponse = httpHeader + "Content-Length: " + to_string(filledPage.length()) + "\r\n\r\n" + filledPage;

	int sendResult = ::send(sockClient, fullResponse.c_str(), fullResponse.length(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr << "发送课程信息页面数据失败: " << WSAGetLastError() << std::endl;
	}

	Sleep(30000);
	::closesocket(sockClient);
}
