#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ����һ���ṹ������ʾѧ����Ϣ
struct Score {
    int stu_id;
    int course_id;
    int score;
};

class ScoreDao
{
public:
    // ����ѧ��ID��CSV�ļ���ȡ��ѧ���ĳɼ���Ϣ
    std::vector<Score> readbyid(int studentId, const std::string& filePath);
    // ���ݿγ�ID��CSV�ļ���ȡѡ�ÿγ̵�ѧ���ɼ���Ϣ
    std::vector<Score> readbycourse(int courseId, const std::string& filePath);
};