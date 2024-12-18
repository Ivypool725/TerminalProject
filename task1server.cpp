#include<iostream>
#include<Windows.h>
#include<string>
#include<unordered_map>
#include<algorithm>
#pragma comment(lib,"ws2_32.lib")
//网络通信需要包含的头文件、需要加载的库文件（很多功能）
#include "task2router.h"


int startup(unsigned short* port)
{
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret)
	{
		std::cout << "Initializing Winsock failed.\n";
		return -1;
	}
	else
		std::cout << "Winsock initialized.\n";
	//1. 创建服务端句柄（套接字）
	SOCKET sockServer = socket(AF_INET,//套接字类型
		SOCK_STREAM,//数据流
		IPPROTO_TCP);//指定协议
	//0);
	if (sockServer == INVALID_SOCKET)//-1
	{
		std::cout << "Failed creating socket.\n";
		WSACleanup();
		return -1;
	}
	else
		printf("1. Socket created\n");


	// 2. 绑定端口号和IP地址
	SOCKADDR_IN server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);//Host - to - Network Short
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//本机地址




	if (bind(sockServer, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Binding failed.\n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}
	printf("2. Binding succeed.\n");

	// 3. 监听端口号(告诉操作系统，与当前程序建立逻辑关联)
	//创建监听队列
	if (listen(sockServer, 5) == SOCKET_ERROR)
	{
		printf("Monitoring port number failed.\n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}
	printf("3. Monitoring port number successful.\n");

	


	return sockServer;// 添加这一行，返回服务器套接字描述符
}

//void handleRegisterRequest(int client, const std::string& requestMethod,
//	const std::string& path, const std::unordered_map<std::string, std::string>& params)
//{
//	std::cout << "Handling register request..." << std::endl;
//	std::string response = "接收到的注册参数如下：\n";
//	// 遍历参数映射，将参数拼接成字符串形式
//	for (const auto& param : params) {
//		response += param.first + " = " + param.second + "\n";
//	}
//
//	// 将响应字符串转换为适合发送的字符数组形式
//	char sendBuff[1024];
//	strcpy(sendBuff, response.c_str());
//	int ret = send(client, sendBuff, strlen(sendBuff), 0);
//	if (ret == SOCKET_ERROR) {
//		std::cout << "向客户端发送注册参数失败" << std::endl;
//	}
//	else {
//		std::cout << "已向客户端发送注册参数" << std::endl;
//	}
//}

//void handleLoginRequest()(int client, const std::string& requestMethod, const std::string& path, const std::unordered_map<std::string, std::string>& params) {
//std::cout << "Handling login request..." << std::endl;
// 实际登录相关业务逻辑代码
//}


//处理用户请求的线程函数
DWORD WINAPI accept_request(LPVOID arg)
{
	char buff[1024];
	int client = (SOCKET)arg;//客户端套接字
	int ret = recv(client, buff, sizeof(buff) - 1, 0);//返回成功接收到的数据字节数

	if (ret > 0)
	{
		buff[ret] = '\0';// 添加字符串结束符
		printf("5. 接收客户端数据成功[%s]\n", buff);//%s表示用于输出字符串
		
		std::string requestData(buff, ret);//构造函数，以接收到的字节数据作为参数，创建了requestData这个字符串对象

		//解析请求
		size_t spacePos = requestData.find(' ');
		if (spacePos == std::string::npos)// 处理请求格式错误情况，这里简单关闭客户端连接示例，实际可更复杂处理
		{
			closesocket(client);
			return 0;
		}

		std::string requestMethod = requestData.substr(0, spacePos);
		std::transform(requestMethod.begin(), requestMethod.end(), requestMethod.begin(),
			[](unsigned char c) {return std::toupper(c); });//lambda表达式


		// 解析路径
		size_t start = requestData.find(' ') + 1;
		size_t end = requestData.find(' ',start);
		std::string path = requestData.substr(start, end - start); //提取字符串的一部分内容
		
		//解析参数
		std::unordered_map<std::string, std::string> params;
		size_t queryStart = requestData.find('?');
		if (queryStart != std::string::npos)
		{
			std::string queryString = requestData.substr(queryStart + 1); //提取出 '?' 后面的所有字符
			size_t pos = 0;
			while (pos < queryString.length())
			{
				size_t keyEnd = queryString.find('=', pos);//从pos位置开始查找‘=’
				std::string key = queryString.substr(pos,keyEnd-pos);
				pos = keyEnd + 1;
				size_t valueEnd = queryString.find('&', pos);
				std::string value = queryString.substr(pos, valueEnd - pos);
				pos = valueEnd + 1;
				params[key] = value;
			}
		}
		
		



		//ret = send(client, buff, ret, 0);

		//if (ret == SOCKET_ERROR)
		//{
		//	printf("发送数据失败\n");
		//	closesocket(client);
		//	return 0; // 发送失败，断开与该客户端的连接
		//}
		//else
		//	if (ret == 0)
		//	{
		//		printf("客户端已主动断开连接。\n");
		//		closesocket(client);
		//		return 0; // 正常退出
		//	}
		//	else // 发生错误
		//	{
		//		printf("接收客户端数据失败\n");
		//		closesocket(client);
		//		return 0; // 错误处理后断开连接
		//	}
	}
	closesocket(client);
	return 0;
}

int main()
{
	unsigned short port_ = 8000;
	//0. 初始化网络环境
	int server_socket = startup(&port_);

	// 4. 接收客户端连接 会建立一个新的套接字(客户端的标记)
	printf("4. Waiting for clients...\n");
	SOCKADDR_IN clientAddr = {};//记录客户网络地址
	int client_addr_len = sizeof(clientAddr);

	std::string input;

	while (true)
	{
		SOCKET sockClient = accept(server_socket, (sockaddr*)&clientAddr, &client_addr_len);
		if (INVALID_SOCKET == sockClient)
		{
			printf("接收客户端连接失败\n");
			continue; // 错误处理后继续等待下一个客户端
		}
		printf("4. Clients accessing successful.\n");


	//创建一个新的线程
	//进程（可包含多个线程）
		DWORD threadId = 0;
		CreateThread(0, 0, accept_request, (void*)sockClient, 0, &threadId);
		
		std::cout << "输入 'quit' 可终止服务器（不区分大小写）。" << std::endl;
		std::cin >> input;
		if (input == "quit" || input == "QUIT")
		{
			break;
		}

	}
	closesocket(server_socket);
	WSACleanup();
	printf("资源已清理\n");
	return 0;
}

