#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <utility>//pair


#pragma comment(lib, "ws2_32.lib")


#include "C:\\Users\\33695\\Desktop\\ter\\view.h"
#include "C:\\Users\\33695\\Desktop\\ter\\scoresService.h"

#include"C:\\Users\\33695\\Desktop\\ter\\routertest.h"
#include"C:\\Users\\33695\\Desktop\\ter\\myRouterTest.h"

using namespace std;
// ��ʼ�����绷�����������󶨡�����������׽���
int startup(unsigned short* port) {
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret) {
        std::cout << "Initializing Winsock failed.\n";
        return -1;
    }
    else {
        std::cout << "Winsock initialized.\n";
    }

    // 1. ��������˾�����׽��֣�
    SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockServer == INVALID_SOCKET) {
        std::cout << "Failed creating socket.\n";
        WSACleanup();
        return -1;
    }
    else {
        std::cout << "1. Socket created\n";
    }

    // 2. �󶨶˿ںź�IP��ַ
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(*port);  // Host-to-Network Short
    server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  // ������ַ

    if (bind(sockServer, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Binding failed.\n";
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    std::cout << "2. Binding succeed.\n";

    // 3. �����˿ں�(���߲���ϵͳ���뵱ǰ�������߼�����)
    // ������������
    if (listen(sockServer, 5) == SOCKET_ERROR) {
        std::cout << "Monitoring port number failed.\n";
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    std::cout << "3. Monitoring port number successful.\n";

    return sockServer;  // ���ط������׽���������
}

pair<string, pair<string, string>> parseHttpRequest(const string& request)
{
    string method;
    string path;
    string params;
    //unordered_map<string, string> params;

    //eg. GET / students ? name = John & age = 20 HTTP / 1.1

    //��һ�У���������
    size_t pos = request.find('\n');
    string requestLine = request.substr(0, pos);
    stringstream ss(requestLine);//stringstream Ĭ�ϻᰴ�տո񣨿հ��ַ����Ʊ���ȿհ����ַ������ָ��ַ�������
    ss >> method;//"GET"
    string pathWithParams;
    ss >> pathWithParams;//"/students?name=John&age=20"

    //�ж���ʽ1
    size_t questionMarkPos = pathWithParams.find('?');
    if (questionMarkPos != string::npos)
    {
        path = pathWithParams.substr(0, questionMarkPos);//"/students"
        string paramStr = pathWithParams.substr(questionMarkPos + 1);//"name=John&age=20"
        params = paramStr;
        
    }
    else//��ʽ2
    {
        size_t slashPos = pathWithParams.find('/');
        if (slashPos != string::npos && slashPos < pathWithParams.size() - 1)//�ڶ����ж������������ǣ�
        {
            path = pathWithParams.substr(0, slashPos);
            string paramValue = pathWithParams.substr(slashPos + 1);
            params = paramValue;
        }
        else
        {
            path = pathWithParams;
            params = " ";
        }
    }
    
    return make_pair(method, make_pair(path, params));
}

int main() {
    unsigned short port_ = 8000;
    // 0. ��ʼ�����绷��
    int server_socket = startup(&port_);

    // 4. ���տͻ������Ӳ�����
    std::cout << "4. Waiting for clients...\n";
    SOCKADDR_IN clientAddr = {};  // ��¼�ͻ������ַ
    int client_addr_len = sizeof(clientAddr);


    MyRouter router;
    router.setupRouting();


    // ѭ�����ղ�����ͻ������ӣ�ֱ���������ر�
    while (true) 
    {
        SOCKET sockClient = accept(server_socket, (sockaddr*)&clientAddr, &client_addr_len);
        
        
        if (sockClient == INVALID_SOCKET) 
        {
            cerr << "���տͻ�������ʧ��: " << WSAGetLastError() << std::endl;
            continue;
        }

        cout << "�ͻ���������\n";
        //���տͻ��˷�����http����
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(sockClient, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == SOCKET_ERROR)
        {
            cerr<<"�ͻ�������ʧ��:"<< WSAGetLastError() << endl;
            closesocket(sockClient);
            continue;
        }
        else if (bytesRead == 0)
        {
            cout << "�ͻ����ѹر�����" << std::endl;
            closesocket(sockClient);
            continue;
        }
        
        string request(buffer, bytesRead);//ʹ�õĹ��캯������ʽ�� string (const char* s, size_t n)

        // ʹ�ú�������HTTP����
        auto parsedResult = parseHttpRequest(request);
        string method = parsedResult.first;
        string path = parsedResult.second.first;
        string params = parsedResult.second.second;
       
        router.handle(method, path, sockClient, params);

       // router.handle(method, path, sockClient, id);

        //router.handle("GET", "/students", sockClient, -1);
        //router.handle("GET", "/scores_by_course", sockClient, 102);
        
        
    }

    closesocket(server_socket);
    WSACleanup();
    std::cout << "��Դ������\n";
    return 0;
}
