#include "courseDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// 读取CSV文件并返回包含课程信息的向量
vector<Course> CourseDao::readCourseFromCsv(const string& filePath) {
    vector<Course> courses;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // 跳过标题行（第一行）
        getline(file, line);
        while (getline(file, line)) {
            Course course;
            stringstream ss(line);
            string field;

            // 读取课程id
            getline(ss, field, ',');
            course.id = stoi(field);

            // 读取课程名称
            getline(ss, field, ',');
            course.name = field;

            // 读取课程时间
            getline(ss, field, ',');
            course.time = field;

            // 读取课程地点，这里不再使用stoi，因为从示例看地点是字符串形式
            getline(ss, field, ',');
            course.location = field;

            // 读取授课教师，同样是字符串形式
            getline(ss, field, ',');
            course.teacher = field;

            courses.push_back(course);
        }
        file.close();
    }
    else {
        cerr << "无法打开文件: " << filePath << endl;
    }
    return courses;
}
