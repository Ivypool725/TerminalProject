#include "CloudStorageController.h"

// ʹ��Ĭ�Ϲ��캯��ʱ�ĳ�ʼ���߼����������Ҫ�ɲ�������ʼ�����룩
CloudStorageController::CloudStorageController() : model(CloudStorageModel()), view(CloudStorageView()) {}

// ���г����߼���Ŀǰ��Ϊ�գ���������Ӹ������ʼ����Դ���߼���ʵ������������server.cpp�е�ѭ������������
void CloudStorageController::run() {}
