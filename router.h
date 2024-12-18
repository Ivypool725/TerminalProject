#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include "Controller/CloudStorageBaseController.h"

// ·�ɽṹ�壬�������󷽷���·���Լ���Ӧ�Ĵ�������ʹ��std::function��װ�������󶨲�ͬ���͵Ŀɵ��ö���
struct Route {
    std::string method;
    std::string path;
    std::function<void(int clientSocket)> handler;
};

// ·����������࣬������·����صĻ��������ӿ�
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

// Router��Ĺ��캯��ʵ��
Router::Router() {}

// ע��·�ɺ���ʵ�֣���·����Ϣ��ӵ�·�ɱ���
void Router::registerRoute(const Route& route) {
    routeTable[route.method + route.path] = route;
}

// ��������ķ�����·�������Ҳ����ö�Ӧ�Ĵ�����������ͻ����׽�����������ͨ�Żظ��Ȳ���
void Router::handleRequest(int clientSocket, std::string method, std::string path) {
    std::string key = method + path;
    auto it = routeTable.find(key);
    if (it != routeTable.end()) {
        it->second.handler(clientSocket);
    }
    else {
        std::cerr << "404 - Route not found for path: " << path << std::endl;
        // ʵ��Ӧ���п���ͻ��˷���404��HTTP��Ӧ��Ϣ���˴���δʵ��
    }
}
