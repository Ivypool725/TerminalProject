#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 定义一个结构体来表示学生信息
struct Student {
    int id;
    string name;
    string sex;
    int age;
};

class StudentDao
{
public:
    vector<Student> readStudentsFromCsv(const string& filePath);
    Student getStudentFromCsv(const string& filePath,int id);
};