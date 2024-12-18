#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// ����Course�ṹ������ʾ�γ���Ϣ
struct Course {
    int id;
    string name;//�γ�����
    string time;
    string location;
    string teacher;
};

class CourseDao {
public:
    vector<Course> readCourseFromCsv(const string& filePath);
    // ���ݿγ�ID��ȡ��Ӧ�Ŀγ���Ϣ
    vector<Course> getCourseByStuId(int stuId, const std::string& filePath);
    Course getCourseByCourseId(int courseId, const std::string& filePath);
};