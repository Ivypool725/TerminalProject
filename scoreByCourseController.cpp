#include"scoreByCourseController.h"

void ScoreByCourseController::setTemplateName_C()
{
	modelAndView.setTemplateName("scores_by_course.htm");
}


void ScoreByCourseController::addTableData_C(int courseid)
{
	modelAndView.addTableData("score-arr-course", "ScoreByCourseService", courseid);
}


void ScoreByCourseController::scoreByCourseContHandle(SOCKET sockClient, string Sid)
{
	setTemplateName_C();

	int id = stoi(Sid);

	addTableData_C(id);

	modelAndView.addCourseAttribute(id);

	//const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
	const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";


	View view;
	string filledPage = view.replaceScoreByCourse(&modelAndView);

	//string fullResponse = httpHeader + filledPage;
	string fullResponse = httpHeader + "Content-Length: " + to_string(filledPage.length()) + "\r\n\r\n" + filledPage;

	int sendResult = ::send(sockClient, fullResponse.c_str(), fullResponse.length(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		std::cerr << "发送学生成绩信息页面数据失败: " << WSAGetLastError() << std::endl;
	}

	Sleep(30000);
	::closesocket(sockClient);
}