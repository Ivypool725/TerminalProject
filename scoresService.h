#pragma once
#include <vector>
#include "scoresDao.h"


using namespace std;

class ScoreService {
public:
    vector<Score> getStudentScoresById(int studentId);
    // ���ݿγ�ID��ȡѡ�ÿγ̵�ѧ���ɼ���Ϣ
    vector<Score> getCourseScoresById(int courseId);
private:
    
    ScoreDao scoresDao;
};