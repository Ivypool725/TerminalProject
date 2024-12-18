#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ����һ���ṹ������ʾѧ����Ϣ
struct Score {
    int stu_id;
    int course_id;
    int score;
};

class ScoreDao
{
public:
    vector<Score> readScoresFromCsv(const string& filePath);
};