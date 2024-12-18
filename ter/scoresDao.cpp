#include "scoresDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// 读取CSV文件并返回包含课程信息的向量
vector<Score> ScoreDao::readScoresFromCsv(const string& filePath) {
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
            score.stu_id = stoi(field);

            
            getline(ss, field, ',');
            score.course_id = stoi(field);

    
            getline(ss, field, ',');
            score.score = stoi(field);

            scores.push_back(score);
        }
        file.close();
    }
    else {
        cerr << "无法打开文件: " << filePath << endl;
    }
    return scores;
}