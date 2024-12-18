#include "scoresDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// 根据学生ID从CSV文件读取该学生的成绩信息
vector<Score> ScoreDao::readbyid(int studentId, const string& filePath) {
    vector<Score> scores;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // 跳过标题行（第一行）
        getline(file, line);
        while (getline(file, line)) {
            Score score;
            stringstream ss(line);
            string field;

            getline(ss, field, ',');
            int currentStuId = stoi(field);
            if (currentStuId == studentId) {
                getline(ss, field, ',');
                score.course_id = stoi(field);

                getline(ss, field, ',');
                score.score = stoi(field);

                scores.push_back(score);
            }
        }
        file.close();
    }
    else {
        cerr << "无法打开文件: " << filePath << endl;
    }
    return scores;
}

// 根据课程ID从CSV文件读取选该课程的学生成绩信息
vector<Score> ScoreDao::readbycourse(int courseId, const string& filePath) {
    vector<Score> scores;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // 跳过标题行（第一行）
        getline(file, line);
        while (getline(file, line))
        {
            Score score;
            stringstream ss(line);
            string field;

            //stu_id
            getline(ss, field, ',');
            score.stu_id = stoi(field);

            //course_id
            getline(ss, field, ',');
            score.course_id = stoi(field);

            //score
            getline(ss, field, ',');
            score.score = stoi(field);

            if (score.course_id == courseId)
            {
                scores.push_back(score);
            }
        }
        file.close();
    }
    else {
        cerr << "无法打开文件: " << filePath << endl;
    }
    return scores;
}
