#pragma once
#include <vector>
#include "studentsDao.h"
using namespace std;

class StudentsService {
public:
    vector<Student> getAllStudents();
    Student getStudent(int id);
private:
    StudentDao studentsDao;
};