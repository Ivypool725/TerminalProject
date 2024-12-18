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

// �Զ���·�����࣬�̳��Գ����Router�࣬�������þ����·�ɹ���
class MyRouter : public Router {
public:
    void setupRouting() override {
        // �ļ��ϴ�·��ע�ᣬ�������󷽷���POST��·���� /upload
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

        // �ļ�����·��ע�ᣬ�������󷽷���GET��·���� /download
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

        // �鿴�����û��ļ�·��ע�ᣬ�������󷽷���GET��·���� /view_other_files
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

        // ��¼·��ע�ᣬ�������󷽷���POST��·���� /login
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

        // �ǳ�·��ע�ᣬ�������󷽷���POST��·���� /logout
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

// �������������������󶨼����׽��֣����ط������׽���������
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

// �����û�������̺߳��������տͻ����׽��֣��������󲢸���·�ɹ��������Ӧ�Ŀ�������������Ȼ����Ӧ���ͻؿͻ���
DWORD WINAPI handleClientRequest(LPVOID arg) {
    int clientSocket = (int)arg;
    char buffer[1024];
    int recvSize = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (recvSize > 0) {
        buffer[recvSize] = '\0';
        std::string requestData(buffer);

        // �������󷽷���ת��Ϊ��д��ʽ
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

        // ��������·��
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
            printf("���տͻ�������ʧ��\n");
            continue;
        }
        printf("4. Clients accessing successful.\n");

        DWORD threadId = 0;
        CreateThread(0, 0, handleClientRequest, (void*)clientSocket, 0, &threadId);

        std::cout << "���� 'quit' ����ֹ�������������ִ�Сд����" << std::endl;
        std::cin >> input;
        if (input == "quit" || input == "QUIT") {
            break;
        }
    }
    closesocket(serverSocket);
    WSACleanup();
    printf("��Դ������\n");
    return 0;
}
