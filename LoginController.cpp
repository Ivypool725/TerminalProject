#include "LoginController.h"

// �����¼�߼�
void LoginController::handle() {
    while (true) {
        view.showLoginMenu();
        std::string username = view.getUserInput();
        view.showLoginMenu();
        std::string password = view.getUserInput();
        if (model.authenticateUser(username, password)) {
            model.setCurrentUser(username);
            view.showMessage("��¼�ɹ�");
            break;
        }
        else {
            view.showMessage("�û����������������������");
        }
    }
}
