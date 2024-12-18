#include "scoresService.h"

// 根据学生ID获取该学生对应的成绩信息
vector<Score> ScoreService::getStudentScoresById(int studentId) {
    return scoresDao.readbyid(studentId, "C:\\Users\\33695\\Desktop\\ter1\\scores.csv");
}

// 根据课程ID获取选该课程的学生成绩信息
vector<Score> ScoreService::getCourseScoresById(int courseId) {
    return scoresDao.readbycourse(courseId, "C:\\Users\\33695\\Desktop\\ter1\\scores.csv");
}
