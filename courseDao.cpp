#include "courseDao.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// ��ȡCSV�ļ������ذ����γ���Ϣ������
vector<Course> CourseDao::readCourseFromCsv(const string& filePath)
{
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

vector<Course> CourseDao::getCourseByStuId(int studentId, const string& filePath) {
    // �ȴ�scores.csv�ļ��л�ȡ��ѧ��ѡ����Щ�γ̣��γ̱�ţ�
    vector<int> selectedCourseIds;
    ifstream scoresFile("scores.csv");
    if (!scoresFile) {
        cerr << "�޷���scores.csv�ļ�" << endl;
        return {};
    }
    string line;
    // ���Զ�ȡ�����У������ȡʧ����˵���ļ���ʽ����������
    if (!getline(scoresFile, line)) {
        cerr << "scores.csv�ļ���ʽ�����޷���ȡ������" << endl;
        return {};
    }
    while (getline(scoresFile, line)) {
        stringstream ss(line);
        string stuIdStr, courseIdStr, scoreStr;
        if (!(getline(ss, stuIdStr, ',') &&
            getline(ss, courseIdStr, ',') &&
            getline(ss, scoreStr, ','))) {
            cerr << "scores.csv�ļ�ĳ�����ݸ�ʽ����" << endl;
            continue;
        }
        int currentStuId = stoi(stuIdStr);
        if (currentStuId == studentId) {
            selectedCourseIds.push_back(stoi(courseIdStr));
        }
    }

    // ��course.csv�ļ��ж�ȡ���пγ���Ϣ�������ļ���ʽΪ���γ̱��,�γ�����,��ʦ,�Ͽ�ʱ��,�Ͽεص㣩
    vector<Course> allCourses = readCourseFromCsv("course.csv");
    if (allCourses.empty()) {
        cerr << "�޷���course.csv�ļ��ж�ȡ���γ���Ϣ" << endl;
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
        std::cerr << "�޷����ļ�: " << filePath << std::endl;
        return Course();
    }

    std::string line;
    // ���������У������ļ���һ���Ǳ�����Ϣ������Ҫ����
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