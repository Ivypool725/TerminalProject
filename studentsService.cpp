#include "studentsService.h"

vector<Student> StudentsService::getAllStudents()
{
	return studentsDao.readStudentsFromCsv("C:\\Users\\33695\\Desktop\\ter1\\students.csv");
}

Student StudentsService::getStudent(int id)
{
	return studentsDao.getStudentFromCsv("C:\\Users\\33695\\Desktop\\ter1\\students.csv", id);
}