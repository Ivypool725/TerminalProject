#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include<Windows.h>

class CloudStorageView {
public:
    void showMessage(const std::string& message, int clientSocket);  // չʾ��Ϣ��������ͻ��˷�����ʾ����Ϣ������ͻ����׽�����ʵ�����緢��
    std::string getUserInput();  // ��ȡ�û����루����ҳ�˳����¿��ܲ�̫���ã��ݱ����ӿڶ��壩
};
