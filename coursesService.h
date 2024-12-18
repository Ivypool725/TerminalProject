#pragma once
#include <vector>
#include "CourseDao.h"
using namespace std;

class CoursesService {
public:
    vector<Course> getAllCourses();
    // 根据课程ID获取特定课程信息
    vector<Course> getCourseByStuId(int courseId);
    Course getCourseByCourseId(int courseId);
private:
    CourseDao coursesDao;
};