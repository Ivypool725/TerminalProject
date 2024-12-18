#pragma once
#include <vector>
#include "scoresDao.h"


using namespace std;

class ScoreService {
public:
    vector<Score> getStudentScoresById(int studentId);
    // 根据课程ID获取选该课程的学生成绩信息
    vector<Score> getCourseScoresById(int courseId);
private:
    
    ScoreDao scoresDao;
};