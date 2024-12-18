#pragma once
#include <vector>
#include "CourseDao.h"
using namespace std;

class CoursesService {
public:
    vector<Course> getAllCourses();
    // ���ݿγ�ID��ȡ�ض��γ���Ϣ
    vector<Course> getCourseByStuId(int courseId);
    Course getCourseByCourseId(int courseId);
private:
    CourseDao coursesDao;
};