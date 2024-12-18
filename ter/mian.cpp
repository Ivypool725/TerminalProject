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
// 初始化网络环境并创建、绑定、监听服务端套接字
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

    // 1. 创建服务端句柄（套接字）
    SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockServer == INVALID_SOCKET) {
        std::cout << "Failed creating socket.\n";
        WSACleanup();
        return -1;
    }
    else {
        std::cout << "1. Socket created\n";
    }

    // 2. 绑定端口号和IP地址
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(*port);  // Host-to-Network Short
    server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  // 本机地址

    if (bind(sockServer, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cout << "Binding failed.\n";
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    std::cout << "2. Binding succeed.\n";

    // 3. 监听端口号(告诉操作系统，与当前程序建立逻辑关联)
    // 创建监听队列
    if (listen(sockServer, 5) == SOCKET_ERROR) {
        std::cout << "Monitoring port number failed.\n";
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    std::cout << "3. Monitoring port number successful.\n";

    return sockServer;  // 返回服务器套接字描述符
}

pair<string, pair<string, string>> parseHttpRequest(const string& request)
{
    string method;
    string path;
    string params;
    //unordered_map<string, string> params;

    //eg. GET / students ? name = John & age = 20 HTTP / 1.1

    //第一行，请求内容
    size_t pos = request.find('\n');
    string requestLine = request.substr(0, pos);
    stringstream ss(requestLine);//stringstream 默认会按照空格（空白字符、制表符等空白类字符）来分割字符串内容
    ss >> method;//"GET"
    string pathWithParams;
    ss >> pathWithParams;//"/students?name=John&age=20"

    //判断形式1
    size_t questionMarkPos = pathWithParams.find('?');
    if (questionMarkPos != string::npos)
    {
        path = pathWithParams.substr(0, questionMarkPos);//"/students"
        string paramStr = pathWithParams.substr(questionMarkPos + 1);//"name=John&age=20"
        params = paramStr;
        
    }
    else//形式2
    {
        size_t slashPos = pathWithParams.find('/');
        if (slashPos != string::npos && slashPos < pathWithParams.size() - 1)//第二个判断条件的作用是？
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
    // 0. 初始化网络环境
    int server_socket = startup(&port_);

    // 4. 接收客户端连接并处理
    std::cout << "4. Waiting for clients...\n";
    SOCKADDR_IN clientAddr = {};  // 记录客户网络地址
    int client_addr_len = sizeof(clientAddr);


    MyRouter router;
    router.setupRouting();


    // 循环接收并处理客户端连接，直到服务器关闭
    while (true) 
    {
        SOCKET sockClient = accept(server_socket, (sockaddr*)&clientAddr, &client_addr_len);
        
        
        if (sockClient == INVALID_SOCKET) 
        {
            cerr << "接收客户端连接失败: " << WSAGetLastError() << std::endl;
            continue;
        }

        cout << "客户端已连接\n";
        //接收客户端发来的http请求
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(sockClient, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == SOCKET_ERROR)
        {
            cerr<<"客户端连接失败:"<< WSAGetLastError() << endl;
            closesocket(sockClient);
            continue;
        }
        else if (bytesRead == 0)
        {
            cout << "客户端已关闭连接" << std::endl;
            closesocket(sockClient);
            continue;
        }
        
        string request(buffer, bytesRead);//使用的构造函数的形式是 string (const char* s, size_t n)

        // 使用函数解析HTTP请求
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
    std::cout << "资源已清理\n";
    return 0;
}
