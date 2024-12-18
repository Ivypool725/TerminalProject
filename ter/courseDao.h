#pragma once
#include <string>
#include <vector>

// 定义Course结构体来表示课程信息
struct Course {
    int id;
    std::string name;
    std::string time;
    std::string location;
    std::string teacher;
};

class CourseDao {
public:
    // 读取CSV文件并返回包含课程信息的向量
    std::vector<Course> readCourseFromCsv(const std::string& filePath);
};