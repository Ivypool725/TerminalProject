#include "scoresDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ��ȡCSV�ļ������ذ����γ���Ϣ������
vector<Score> ScoreDao::readScoresFromCsv(const string& filePath) {
    vector<Score> scores;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // ���������У���һ�У�
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
        cerr << "�޷����ļ�: " << filePath << endl;
    }
    return scores;
}