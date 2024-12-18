#include "LogoutController.h"

// 处理登出逻辑
void LogoutController::handle() {
    model.clearCurrentUser();
    view.showMessage("已登出。");
}
