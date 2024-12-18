#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "controllertest.h"

using namespace std;

#define REGISTER_CTRL_FUN(method,path,className,fun) addRouting(method,path,new className,(CTRL_FUN)&className::##fun)

//typedef void (Controller::* CTRL_FUN)(string, SOCKET, int);
typedef void (Controller::* CTRL_FUN)(SOCKET, string);
//typedef void (Controller::* CTRL_FUN)(string,int,int);


struct RoutingElement
{
    string method;
    string path;
    Controller* object;
    CTRL_FUN fun;
};

class Router
{
public:
    Router();
    virtual void setupRouting() = 0;//子类完成
    void handle(string method, string path, SOCKET clientSocket, string Para);//单纯的调用，暂且不管

private:
    vector<RoutingElement> table;

protected:
    void addRouting(string method, string path, Controller* obj, CTRL_FUN fun);
};

