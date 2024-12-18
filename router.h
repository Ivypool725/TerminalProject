#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include "Controller/CloudStorageBaseController.h"

// 路由结构体，包含请求方法、路径以及对应的处理函数（使用std::function包装，可灵活绑定不同类型的可调用对象）
struct Route {
    std::string method;
    std::string path;
    std::function<void(int clientSocket)> handler;
};

// 路由器抽象基类，定义了路由相关的基本操作接口
class Router {
public:
    Router();
    virtual ~Router() {}
    virtual void setupRouting() = 0;
    void handleRequest(int clientSocket, std::string method, std::string path);

protected:
    void registerRoute(const Route& route);
    std::unordered_map<std::string, Route> routeTable;
};

// Router类的构造函数实现
Router::Router() {}

// 注册路由函数实现，将路由信息添加到路由表中
void Router::registerRoute(const Route& route) {
    routeTable[route.method + route.path] = route;
}

// 根据请求的方法和路径来查找并调用对应的处理函数，传入客户端套接字用于网络通信回复等操作
void Router::handleRequest(int clientSocket, std::string method, std::string path) {
    std::string key = method + path;
    auto it = routeTable.find(key);
    if (it != routeTable.end()) {
        it->second.handler(clientSocket);
    }
    else {
        std::cerr << "404 - Route not found for path: " << path << std::endl;
        // 实际应用中可向客户端发送404的HTTP响应消息，此处简化未实现
    }
}
