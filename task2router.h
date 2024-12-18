#pragma once
#include<string>
#include<unordered_map>
#include "CloudStorageBaseController.h"


#define DECLARE_CTRL_FUN(n) public: virtual void f##n(string a);
#define IMPLEMENT_CTRL_FUN(className,n,funName) void className::f##n(string a) { funName(a); }
#define REGISTER_CTRL_FUN(method,path,className,n) registerRoute(method,path,new className,(CTRL_FUN)&className::f##n);

//using RequestHandler = void(*)(int client, const std::string& requestMethod, const std::string& path, 
//	const std::unordered_map<std::string, std::string>& params);

typedef void (CloudStorageBaseController::* CTRL_FUN)(std::string);


struct Route// 路由结构体，包含路径和对应的处理函数指针
{
	std::string method;
	std::string path;
	CloudStorageBaseController* controllerObj;//指向一个继承自Controller类的对象
	CTRL_FUN fun; //指向了Controller类（或其子类）中的一个具体成员函数
	//这里直接用指针还是定义一个宏比较好？值得探讨

};

class Router
{
public:
	Router();
	virtual void setupRouting() = 0;
	void handleRequest(std::string method, std::string path);

protected:
	void registerRoute(std::string method, std::string path, CloudStorageBaseController* obj, CTRL_FUN fun);
	//添加到路由表

private:
	std::unordered_map<std::string, Route> routeTable;// 路由表，使用无序映射来存储路由，方便快速查找
	//重要的内部数据结构
};


