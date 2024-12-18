#include "coursesService.h"

vector<Course> CoursesService::getAllCourses()
{
	return coursesDao.readCourseFromCsv("C:\\Users\\33695\\Desktop\\ter1\\courses.csv");
}

vector<Course> CoursesService::getCourseByStuId(int studentId)
{
	return coursesDao.getCourseByStuId(studentId, "C:\\Users\\33695\\Desktop\\ter\\courses.csv");
}

Course CoursesService::getCourseByCourseId(int courseId)
{
	return coursesDao.getCourseByCourseId(courseId, "C:\\Users\\33695\\Desktop\\ter\\courses.csv");
}

