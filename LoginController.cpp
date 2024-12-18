#include "LoginController.h"

// 处理登录逻辑
void LoginController::handle() {
    while (true) {
        view.showLoginMenu();
        std::string username = view.getUserInput();
        view.showLoginMenu();
        std::string password = view.getUserInput();
        if (model.authenticateUser(username, password)) {
            model.setCurrentUser(username);
            view.showMessage("登录成功");
            break;
        }
        else {
            view.showMessage("用户名或密码错误，请重新输入");
        }
    }
}
