#include "scoresDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ����ѧ��ID��CSV�ļ���ȡ��ѧ���ĳɼ���Ϣ
vector<Score> ScoreDao::readbyid(int studentId, const string& filePath) {
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
        cerr << "�޷����ļ�: " << filePath << endl;
    }
    return scores;
}

// ���ݿγ�ID��CSV�ļ���ȡѡ�ÿγ̵�ѧ���ɼ���Ϣ
vector<Score> ScoreDao::readbycourse(int courseId, const string& filePath) {
    vector<Score> scores;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // ���������У���һ�У�
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
        cerr << "�޷����ļ�: " << filePath << endl;
    }
    return scores;
}
