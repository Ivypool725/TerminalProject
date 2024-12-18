#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ����һ���ṹ������ʾѧ����Ϣ
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