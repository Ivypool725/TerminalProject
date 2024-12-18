#include "studentsDao.h"

vector<Student> StudentDao::readStudentsFromCsv(const string& filePath)
{
	vector<Student> students;
	ifstream file(filePath);
	if (file.is_open())
	{
		string line;
		getline(file, line);
		while (getline(file, line))
		{
			Student student;
			stringstream ss(line);
			string field;

			getline(ss, field, ',');
			student.id = stoi(field);
			getline(ss, field, ',');
			student.name = field;
			getline(ss, field, ',');
			student.sex = field;
			getline(ss, field, ',');
			student.age = stoi(field);

			students.push_back(student);

		}
		file.close();

	}
	else
	{
		cerr << "无法打开文件: " << filePath << endl;
	}
	return students;
}

Student StudentDao::getStudentFromCsv(const string& filePath,int id)
{
    Student student;  // 先初始化一个默认的Student对象，用于在没找到对应学生时返回
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // 读取首行（标题行），可根据实际情况决定是否需要处理这一行数据
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string field;

            // 读取学生ID
            getline(ss, field, ',');
            int currentId = stoi(field);
            if (currentId == id) {  // 如果找到匹配的ID
                // 读取学生姓名
                getline(ss, field, ',');
                student.name = field;
                // 读取学生性别
                getline(ss, field, ',');
                student.sex = field;
                // 读取学生年龄
                getline(ss, field, ',');
                student.age = stoi(field);
                student.id = id;  // 设置学生的ID为传入要查找的ID
                break;  // 找到后就可以结束循环了
            }
            // 如果当前行学生ID不匹配，继续读取下一行
        }
        file.close();
    }
    else {
        cerr << "无法打开文件: " << filePath << endl;
    }
    return student;
}