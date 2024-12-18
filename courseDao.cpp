#include "courseDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// 读取CSV文件并返回包含课程信息的向量
vector<Course> CourseDao::readCourseFromCsv(const string& filePath)
{
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

vector<Course> CourseDao::getCourseByStuId(int studentId, const string& filePath) {
    // 先从scores.csv文件中获取该学生选了哪些课程（课程编号）
    vector<int> selectedCourseIds;
    ifstream scoresFile("scores.csv");
    if (!scoresFile) {
        cerr << "无法打开scores.csv文件" << endl;
        return {};
    }
    string line;
    // 尝试读取标题行，如果读取失败则说明文件格式可能有问题
    if (!getline(scoresFile, line)) {
        cerr << "scores.csv文件格式错误，无法读取标题行" << endl;
        return {};
    }
    while (getline(scoresFile, line)) {
        stringstream ss(line);
        string stuIdStr, courseIdStr, scoreStr;
        if (!(getline(ss, stuIdStr, ',') &&
            getline(ss, courseIdStr, ',') &&
            getline(ss, scoreStr, ','))) {
            cerr << "scores.csv文件某行数据格式错误" << endl;
            continue;
        }
        int currentStuId = stoi(stuIdStr);
        if (currentStuId == studentId) {
            selectedCourseIds.push_back(stoi(courseIdStr));
        }
    }

    // 从course.csv文件中读取所有课程信息（假设文件格式为：课程编号,课程名称,教师,上课时间,上课地点）
    vector<Course> allCourses = readCourseFromCsv("course.csv");
    if (allCourses.empty()) {
        cerr << "无法从course.csv文件中读取到课程信息" << endl;
        return {};
    }
    vector<Course> studentCourses;
    for (int courseId : selectedCourseIds) {
        auto it = find_if(allCourses.begin(), allCourses.end(), [courseId](const Course& c) {
            return c.id == courseId;
            });
        if (it != allCourses.end()) {
            studentCourses.push_back(*it);
        }
    }
    return studentCourses;
}



Course CourseDao::getCourseByCourseId(int courseId, const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "无法打开文件: " << filePath << std::endl;
        return Course();
    }

    std::string line;
    // 跳过标题行（假设文件第一行是标题信息，不需要处理）
    if (std::getline(file, line)) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, time, location, teacher;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, time, ',');
            std::getline(ss, location, ',');
            std::getline(ss, teacher, ',');

            int currentId = std::stoi(idStr);
            if (currentId == courseId) {
                Course result;
                result.id = currentId;
                result.name = name;
                result.time = time;
                result.location = location;
                result.teacher = teacher;
                return result;
            }
        }
    }

    return Course();
}