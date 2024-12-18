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


struct Route// ·�ɽṹ�壬����·���Ͷ�Ӧ�Ĵ�����ָ��
{
	std::string method;
	std::string path;
	CloudStorageBaseController* controllerObj;//ָ��һ���̳���Controller��Ķ���
	CTRL_FUN fun; //ָ����Controller�ࣨ�������ࣩ�е�һ�������Ա����
	//����ֱ����ָ�뻹�Ƕ���һ����ȽϺã�ֵ��̽��

};

class Router
{
public:
	Router();
	virtual void setupRouting() = 0;
	void handleRequest(std::string method, std::string path);

protected:
	void registerRoute(std::string method, std::string path, CloudStorageBaseController* obj, CTRL_FUN fun);
	//��ӵ�·�ɱ�

private:
	std::unordered_map<std::string, Route> routeTable;// ·�ɱ�ʹ������ӳ�����洢·�ɣ�������ٲ���
	//��Ҫ���ڲ����ݽṹ
};


