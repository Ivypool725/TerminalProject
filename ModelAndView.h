#pragma once
#include<iostream>
#include<unordered_map>
#include<string>

#include "studentsDao.h"
#include "scoresDao.h"
#include "courseDao.h"
#include "studentsService.h"
#include "coursesService.h"
#include "scoresService.h"



using namespace std;

struct DataTable
{
    vector<string>columnName;
    vector<vector<string>>data;
};

class ModelAndView
{
private:
    string templateName;
    unordered_map<string, string> attributes;
    unordered_map<string, shared_ptr<DataTable>> tableData;
public:
    // ����ҳ��ģ���ļ���
    void setTemplateName(const string& templateName);

    string readTemplate(const string&);

    // ���һ���Եļ�ֵ��������ݣ���Student�ȶ����ȡ���������䣩
    void addStudentAttribute(int id);

    void addCourseAttribute(int courseId);

   
    // ͨ�����������Dao����������ݣ��Գɼ����ݱ��Ϊ��������չ������������ݣ�
    void addTableData(const string& key, const string& serviceType, const int id);
    
    // ��ȡҳ��ģ���ļ���
    string getTemplateName() const;
   
   
    
    // ��ȡһ���Եļ�ֵ��������ݣ�������������ӳ�䣩
    unordered_map<std::string, std::string> getAttributes() const;
    
    
    // ��ȡ���ڱ��ѭ�����������ݱ����
    unordered_map<std::string, std::shared_ptr<DataTable>> getTableData() const;
};
