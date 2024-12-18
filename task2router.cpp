#include<iostream>
#include"task2router.h"

Router* thisRouter;

Router::Router()
{
	thisRouter = this;
}

void Router::registerRoute(std::string method, std::string path, CloudStorageBaseController* obj, CTRL_FUN fun)
{
	Route route = { method, path, obj, fun };
	routeTable[path] = route;
}

void Router::handleRequest(std::string method, std::string path)
{
	auto it = routeTable.find(path);
	if (it != routeTable.end())
	{
		if(it != routeTable.end() && it->second.controllerObj != nullptr) {
			//const std::unordered_map<std::string, std::string>& params = {};
			((*it->second.controllerObj).*(it->second.fun))(path);//??????whhhhhhyyyyy is this place wrong
		}
		else 
		{
		std::cout << "Error: Controller object pointer is null for path: " << path << std::endl;
		}
	}
	else
	{
		std::cout << "404 - Route not found for path: " << path << std::endl;
	}
}

int main()
{
	thisRouter->setupRouting();
	// test
	thisRouter->handleRequest("GET", "/students/getall");
	thisRouter->handleRequest("GET", "/students/getbyage");

	return 0;
}
