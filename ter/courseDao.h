#pragma once
#include <string>
#include <vector>

// ����Course�ṹ������ʾ�γ���Ϣ
struct Course {
    int id;
    std::string name;
    std::string time;
    std::string location;
    std::string teacher;
};

class CourseDao {
public:
    // ��ȡCSV�ļ������ذ����γ���Ϣ������
    std::vector<Course> readCourseFromCsv(const std::string& filePath);
};