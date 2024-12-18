#include <iostream>
#include <Windows.h>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#pragma comment(lib, "ws2_32.lib")
#include "Model/CloudStorageModel.h"
#include "View/CloudStorageView.h"
#include "Controller/CloudStorageBaseController.h"
#include "Controller/CloudStorageController.h"
#include "Controller/FileUploadController.h"
#include "Controller/FileDownloadController.h"
#include "Controller/OtherUsersFilesViewerController.h"
#include "Controller/LoginController.h"
#include "Controller/LogoutController.h"
#include "task2router.h"

// 自定义路由器类，继承自抽象的Router类，用于设置具体的路由规则
class MyRouter : public Router {
public:
    void setupRouting() override {
        // 文件上传路由注册，假设请求方法是POST，路径是 /upload
        Route uploadRoute{
            "POST",
            "/upload",
            [](int clientSocket) {
                CloudStorageModel model;
                CloudStorageView view;
                FileUploadController controller(model, view);
                controller.handle(clientSocket);
            }
        };
        registerRoute(uploadRoute);

        // 文件下载路由注册，假设请求方法是GET，路径是 /download
        Route downloadRoute{
            "GET",
            "/download",
            [](int clientSocket) {
                CloudStorageModel model;
                CloudStorageView view;
                FileDownloadController controller(model, view);
                controller.handle(clientSocket);
            }
        };
        registerRoute(downloadRoute);

        // 查看其他用户文件路由注册，假设请求方法是GET，路径是 /view_other_files
        Route viewOtherFilesRoute{
            "GET",
            "/view_other_files",
            [](int clientSocket) {
                CloudStorageModel model;
                CloudStorageView view;
                OtherUsersFilesViewerController controller(model, view);
                controller.handle(clientSocket);
            }
        };
        registerRoute(viewOtherFilesRoute);

        // 登录路由注册，假设请求方法是POST，路径是 /login
        Route loginRoute{
            "POST",
            "/login",
            [](int clientSocket) {
                CloudStorageModel model;
                CloudStorageView view;
                LoginController controller(model, view);
                controller.handle(clientSocket);
            }
        };
        registerRoute(loginRoute);

        // 登出路由注册，假设请求方法是POST，路径是 /logout
        Route logoutRoute{
            "POST",
            "/logout",
            [](int clientSocket) {
                CloudStorageModel model;
                CloudStorageView view;
                LogoutController controller(model, view);
                controller.handle(clientSocket);
            }
        };
        registerRoute(logoutRoute);
    }
};

// 启动服务器，创建并绑定监听套接字，返回服务器套接字描述符
int startup(unsigned short* port) {
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret) {
        std::cout << "Initializing Winsock failed.\n";
        return -1;
    }
    else
        std::cout << "Winsock initialized.\n";

    SOCKET sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockServer == INVALID_SOCKET) {
        std::cout << "Failed creating socket.\n";
        WSACleanup();
        return -1;
    }
    else
        printf("1. Socket created\n");

    SOCKADDR_IN server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(*port);
    server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if (bind(sockServer, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Binding failed.\n");
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    printf("2. Binding succeed.\n");

    if (listen(sockServer, 5) == SOCKET_ERROR) {
        printf("Monitoring port number failed.\n");
        closesocket(sockServer);
        WSACleanup();
        return -1;
    }
    printf("3. Monitoring port number successful.\n");

    return sockServer;
}

// 处理用户请求的线程函数，接收客户端套接字，解析请求并根据路由规则调用相应的控制器处理函数，然后将响应发送回客户端
DWORD WINAPI handleClientRequest(LPVOID arg) {
    int clientSocket = (int)arg;
    char buffer[1024];
    int recvSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (recvSize > 0) {
        buffer[recvSize] = '\0';
        std::string requestData(buffer);

        // 解析请求方法，转换为大写形式
        size_t spacePos = requestData.find(' ');
        if (spacePos == std::string::npos) {
            std::string response = "Invalid request format";
            send(clientSocket, response.c_str(), response.length(), 0);
            closesocket(clientSocket);
            return 0;
        }
        std::string requestMethod = requestData.substr(0, spacePos);
        std::transform(requestMethod.begin(), requestMethod.end(), requestMethod.begin(),
            [](unsigned char c) { return std::toupper(c); });

        // 解析请求路径
        size_t start = requestData.find(' ') + 1;
        size_t end = requestData.find(' ', start);
        std::string path = requestData.substr(start, end - start);

        MyRouter router;
        router.setupRouting();
        router.handleRequest(clientSocket, requestMethod, path);

    }
    else {
        std::string response = "Failed to receive request data";
        send(clientSocket, response.c_str(), response.length(), 0);
    }
    closesocket(clientSocket);
    return 0;
}

int main() {
    unsigned short port_ = 8000;
    int serverSocket = startup(&port_);
    printf("4. Waiting for clients...\n");
    SOCKADDR_IN clientAddr = {};
    int client_addr_len = sizeof(clientAddr);

    std::string input;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &client_addr_len);
        if (INVALID_SOCKET == clientSocket) {
            printf("接收客户端连接失败\n");
            continue;
        }
        printf("4. Clients accessing successful.\n");

        DWORD threadId = 0;
        CreateThread(0, 0, handleClientRequest, (void*)clientSocket, 0, &threadId);

        std::cout << "输入 'quit' 可终止服务器（不区分大小写）。" << std::endl;
        std::cin >> input;
        if (input == "quit" || input == "QUIT") {
            break;
        }
    }
    closesocket(serverSocket);
    WSACleanup();
    printf("资源已清理\n");
    return 0;
}
