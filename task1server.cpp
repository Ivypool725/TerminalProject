#include<iostream>
#include<Windows.h>
#include<string>
#include<unordered_map>
#include<algorithm>
#pragma comment(lib,"ws2_32.lib")
//����ͨ����Ҫ������ͷ�ļ�����Ҫ���صĿ��ļ����ܶ๦�ܣ�
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
	//1. ��������˾�����׽��֣�
	SOCKET sockServer = socket(AF_INET,//�׽�������
		SOCK_STREAM,//������
		IPPROTO_TCP);//ָ��Э��
	//0);
	if (sockServer == INVALID_SOCKET)//-1
	{
		std::cout << "Failed creating socket.\n";
		WSACleanup();
		return -1;
	}
	else
		printf("1. Socket created\n");


	// 2. �󶨶˿ںź�IP��ַ
	SOCKADDR_IN server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);//Host - to - Network Short
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//������ַ




	if (bind(sockServer, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Binding failed.\n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}
	printf("2. Binding succeed.\n");

	// 3. �����˿ں�(���߲���ϵͳ���뵱ǰ�������߼�����)
	//������������
	if (listen(sockServer, 5) == SOCKET_ERROR)
	{
		printf("Monitoring port number failed.\n");
		closesocket(sockServer);
		WSACleanup();
		return -1;
	}
	printf("3. Monitoring port number successful.\n");

	


	return sockServer;// �����һ�У����ط������׽���������
}

//void handleRegisterRequest(int client, const std::string& requestMethod,
//	const std::string& path, const std::unordered_map<std::string, std::string>& params)
//{
//	std::cout << "Handling register request..." << std::endl;
//	std::string response = "���յ���ע��������£�\n";
//	// ��������ӳ�䣬������ƴ�ӳ��ַ�����ʽ
//	for (const auto& param : params) {
//		response += param.first + " = " + param.second + "\n";
//	}
//
//	// ����Ӧ�ַ���ת��Ϊ�ʺϷ��͵��ַ�������ʽ
//	char sendBuff[1024];
//	strcpy(sendBuff, response.c_str());
//	int ret = send(client, sendBuff, strlen(sendBuff), 0);
//	if (ret == SOCKET_ERROR) {
//		std::cout << "��ͻ��˷���ע�����ʧ��" << std::endl;
//	}
//	else {
//		std::cout << "����ͻ��˷���ע�����" << std::endl;
//	}
//}

//void handleLoginRequest()(int client, const std::string& requestMethod, const std::string& path, const std::unordered_map<std::string, std::string>& params) {
//std::cout << "Handling login request..." << std::endl;
// ʵ�ʵ�¼���ҵ���߼�����
//}


//�����û�������̺߳���
DWORD WINAPI accept_request(LPVOID arg)
{
	char buff[1024];
	int client = (SOCKET)arg;//�ͻ����׽���
	int ret = recv(client, buff, sizeof(buff) - 1, 0);//���سɹ����յ��������ֽ���

	if (ret > 0)
	{
		buff[ret] = '\0';// ����ַ���������
		printf("5. ���տͻ������ݳɹ�[%s]\n", buff);//%s��ʾ��������ַ���
		
		std::string requestData(buff, ret);//���캯�����Խ��յ����ֽ�������Ϊ������������requestData����ַ�������

		//��������
		size_t spacePos = requestData.find(' ');
		if (spacePos == std::string::npos)// ���������ʽ�������������򵥹رտͻ�������ʾ����ʵ�ʿɸ����Ӵ���
		{
			closesocket(client);
			return 0;
		}

		std::string requestMethod = requestData.substr(0, spacePos);
		std::transform(requestMethod.begin(), requestMethod.end(), requestMethod.begin(),
			[](unsigned char c) {return std::toupper(c); });//lambda���ʽ


		// ����·��
		size_t start = requestData.find(' ') + 1;
		size_t end = requestData.find(' ',start);
		std::string path = requestData.substr(start, end - start); //��ȡ�ַ�����һ��������
		
		//��������
		std::unordered_map<std::string, std::string> params;
		size_t queryStart = requestData.find('?');
		if (queryStart != std::string::npos)
		{
			std::string queryString = requestData.substr(queryStart + 1); //��ȡ�� '?' ����������ַ�
			size_t pos = 0;
			while (pos < queryString.length())
			{
				size_t keyEnd = queryString.find('=', pos);//��posλ�ÿ�ʼ���ҡ�=��
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
		//	printf("��������ʧ��\n");
		//	closesocket(client);
		//	return 0; // ����ʧ�ܣ��Ͽ���ÿͻ��˵�����
		//}
		//else
		//	if (ret == 0)
		//	{
		//		printf("�ͻ����������Ͽ����ӡ�\n");
		//		closesocket(client);
		//		return 0; // �����˳�
		//	}
		//	else // ��������
		//	{
		//		printf("���տͻ�������ʧ��\n");
		//		closesocket(client);
		//		return 0; // �������Ͽ�����
		//	}
	}
	closesocket(client);
	return 0;
}

int main()
{
	unsigned short port_ = 8000;
	//0. ��ʼ�����绷��
	int server_socket = startup(&port_);

	// 4. ���տͻ������� �Ὠ��һ���µ��׽���(�ͻ��˵ı��)
	printf("4. Waiting for clients...\n");
	SOCKADDR_IN clientAddr = {};//��¼�ͻ������ַ
	int client_addr_len = sizeof(clientAddr);

	std::string input;

	while (true)
	{
		SOCKET sockClient = accept(server_socket, (sockaddr*)&clientAddr, &client_addr_len);
		if (INVALID_SOCKET == sockClient)
		{
			printf("���տͻ�������ʧ��\n");
			continue; // �����������ȴ���һ���ͻ���
		}
		printf("4. Clients accessing successful.\n");


	//����һ���µ��߳�
	//���̣��ɰ�������̣߳�
		DWORD threadId = 0;
		CreateThread(0, 0, accept_request, (void*)sockClient, 0, &threadId);
		
		std::cout << "���� 'quit' ����ֹ�������������ִ�Сд����" << std::endl;
		std::cin >> input;
		if (input == "quit" || input == "QUIT")
		{
			break;
		}

	}
	closesocket(server_socket);
	WSACleanup();
	printf("��Դ������\n");
	return 0;
}

