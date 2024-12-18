#include "courseDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ��ȡCSV�ļ������ذ����γ���Ϣ������
vector<Course> CourseDao::readCourseFromCsv(const string& filePath) {
    vector<Course> courses;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // ���������У���һ�У�
        getline(file, line);
        while (getline(file, line)) {
            Course course;
            stringstream ss(line);
            string field;

            // ��ȡ�γ�id
            getline(ss, field, ',');
            course.id = stoi(field);

            // ��ȡ�γ�����
            getline(ss, field, ',');
            course.name = field;

            // ��ȡ�γ�ʱ��
            getline(ss, field, ',');
            course.time = field;

            // ��ȡ�γ̵ص㣬���ﲻ��ʹ��stoi����Ϊ��ʾ�����ص����ַ�����ʽ
            getline(ss, field, ',');
            course.location = field;

            // ��ȡ�ڿν�ʦ��ͬ�����ַ�����ʽ
            getline(ss, field, ',');
            course.teacher = field;

            courses.push_back(course);
        }
        file.close();
    }
    else {
        cerr << "�޷����ļ�: " << filePath << endl;
    }
    return courses;
}
