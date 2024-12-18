#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 定义一个结构体来表示学生信息
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