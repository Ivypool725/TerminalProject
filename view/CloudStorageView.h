#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include<Windows.h>

class CloudStorageView {
public:
    void showMessage(const std::string& message, int clientSocket);  // 展示消息，用于向客户端返回提示等信息，传入客户端套接字以实现网络发送
    std::string getUserInput();  // 获取用户输入（在网页端场景下可能不太适用，暂保留接口定义）
};
