#include "LogoutController.h"

// ����ǳ��߼�
void LogoutController::handle() {
    model.clearCurrentUser();
    view.showMessage("�ѵǳ���");
}
