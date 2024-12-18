#include "studentsControllerTest.h"



void StudentsController::setTemplateName_C()
{
	modelAndView.setTemplateName("students.htm");
}
void StudentsController::addTableData_C()
{
	modelAndView.addTableData("stu-arr", "StudentService", -1);
}

void StudentsController::stuContHandle(SOCKET sockClient, string  invalidPara)
{
	setTemplateName_C();

	addTableData_C();
	//const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: Keep-Alive\r\n\r\n";
    const string httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";

    View view;
    string filledPage=view.replaceStuTableData(&modelAndView);//专职化

    //string fullResponse = httpHeader + filledPage;
    string fullResponse = httpHeader + "Content-Length: " + to_string(filledPage.length()) + "\r\n\r\n" + filledPage;

    int sendResult = ::send(sockClient, fullResponse.c_str(), fullResponse.length(), 0);
    if (sendResult == SOCKET_ERROR)
    {
        std::cerr << "发送学生成绩信息页面数据失败: " << WSAGetLastError() << std::endl;
    }

    ::closesocket(sockClient);
}



