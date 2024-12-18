#include "studentsDao.h"

vector<Student> StudentsDao::readStudentsFromCsv(const string& filePath)
{
	vector<Student> students;
	ifstream file(filePath);
	if (file.is_open())
	{
		cerr << "File opened.\n";
		string line;
		getline(file, line);
		while (getline(file, line))
		{
			Student student;
			stringstream ss(line);//?
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