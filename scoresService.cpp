#include "scoresService.h"

// ����ѧ��ID��ȡ��ѧ����Ӧ�ĳɼ���Ϣ
vector<Score> ScoreService::getStudentScoresById(int studentId) {
    return scoresDao.readbyid(studentId, "C:\\Users\\33695\\Desktop\\ter1\\scores.csv");
}

// ���ݿγ�ID��ȡѡ�ÿγ̵�ѧ���ɼ���Ϣ
vector<Score> ScoreService::getCourseScoresById(int courseId) {
    return scoresDao.readbycourse(courseId, "C:\\Users\\33695\\Desktop\\ter1\\scores.csv");
}
