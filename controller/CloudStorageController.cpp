#include "CloudStorageController.h"

// 使用默认构造函数时的初始化逻辑（如果有需要可补充更多初始化代码）
CloudStorageController::CloudStorageController() : model(CloudStorageModel()), view(CloudStorageView()) {}

// 运行程序逻辑，目前暂为空，后续可添加更多如初始化资源等逻辑，实际运行依赖于server.cpp中的循环接收请求处理
void CloudStorageController::run() {}
