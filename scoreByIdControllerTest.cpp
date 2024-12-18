#include "scoreByIdControllerTest.h"


void ScoreByIdController::setTemplateName_C()
{
	modelAndView.setTemplateName("scores_by_stu.htm");
}
void ScoreByIdController::addTableData_C(int id)
{
	modelAndView.addTableData("score-arr-id", "ScoreByIdService", id);
}

void ScoreByIdController::scoreByIdContHandle(SOCKET sockClient, string Sid)
{
	setTemplateName_C();

	int id = stoi(Sid);

	addTableData_C(id);

	modelAndView.addStudentAttribute(id);

	//const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
	const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";

	View view;
	string filledPage = view.replaceScoreById(&modelAndView);

	//string fullResponse = httpHeader + filledPage;
	string fullResponse = httpHeader + "Content-Length: " + to_string(filledPage.length()) + "\r\n\r\n" + filledPage;


	int sendResult = ::send(sockClient, fullResponse.c_str(), fullResponse.length(), 0);
	if (sendResult == SOCKET_ERROR)
	{
		cerr << "发送学生成绩信息页面数据失败: " << WSAGetLastError() << std::endl;
	}

	//Sleep(30000);
	::closesocket(sockClient);
}



