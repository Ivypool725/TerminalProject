#include "routertest.h"

Router* thisRouter;
Router::Router()
{
    thisRouter = this;
}

void Router::addRouting(string method, string path, Controller* obj, CTRL_FUN fun)
{
    RoutingElement ele;
    ele.method = method;
    ele.path = path;
    ele.object = obj;
    ele.fun = fun;
    table.push_back(ele);
}

void Router::handle(string method, string path, SOCKET clientSocket, string Para)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].method == method && table[i].path == path)
        {
            string a = "";
            ((*table[i].object).*(table[i].fun))(clientSocket, Para);
            
            break;
        }
    }
}

