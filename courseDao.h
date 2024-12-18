#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// 定义Course结构体来表示课程信息
struct Course {
    int id;
    string name;//课程名称
    string time;
    string location;
    string teacher;
};

class CourseDao {
public:
    vector<Course> readCourseFromCsv(const string& filePath);
    // 根据课程ID获取对应的课程信息
    vector<Course> getCourseByStuId(int stuId, const std::string& filePath);
    Course getCourseByCourseId(int courseId, const std::string& filePath);
};