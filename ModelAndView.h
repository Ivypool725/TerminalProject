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
    // 设置页面模板文件名
    void setTemplateName(const string& templateName);

    string readTemplate(const string&);

    // 添加一般性的键值对填充数据（从Student等对象获取相关属性填充）
    void addStudentAttribute(int id);

    void addCourseAttribute(int courseId);

   
    // 通过服务类调用Dao来填充表格数据（以成绩数据表格为例，可扩展到其他表格数据）
    void addTableData(const string& key, const string& serviceType, const int id);
    
    // 获取页面模板文件名
    string getTemplateName() const;
   
   
    
    // 获取一般性的键值对填充数据（返回用于填充的映射）
    unordered_map<std::string, std::string> getAttributes() const;
    
    
    // 获取用于表格、循环性填充的数据表对象
    unordered_map<std::string, std::shared_ptr<DataTable>> getTableData() const;
};
