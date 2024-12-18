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
    // 根据学生ID从CSV文件读取该学生的成绩信息
    std::vector<Score> readbyid(int studentId, const std::string& filePath);
    // 根据课程ID从CSV文件读取选该课程的学生成绩信息
    std::vector<Score> readbycourse(int courseId, const std::string& filePath);
};