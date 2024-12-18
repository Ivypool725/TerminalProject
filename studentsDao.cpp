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
		cerr << "�޷����ļ�: " << filePath << endl;
	}
	return students;
}

Student StudentDao::getStudentFromCsv(const string& filePath,int id)
{
    Student student;  // �ȳ�ʼ��һ��Ĭ�ϵ�Student����������û�ҵ���Ӧѧ��ʱ����
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        // ��ȡ���У������У����ɸ���ʵ����������Ƿ���Ҫ������һ������
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string field;

            // ��ȡѧ��ID
            getline(ss, field, ',');
            int currentId = stoi(field);
            if (currentId == id) {  // ����ҵ�ƥ���ID
                // ��ȡѧ������
                getline(ss, field, ',');
                student.name = field;
                // ��ȡѧ���Ա�
                getline(ss, field, ',');
                student.sex = field;
                // ��ȡѧ������
                getline(ss, field, ',');
                student.age = stoi(field);
                student.id = id;  // ����ѧ����IDΪ����Ҫ���ҵ�ID
                break;  // �ҵ���Ϳ��Խ���ѭ����
            }
            // �����ǰ��ѧ��ID��ƥ�䣬������ȡ��һ��
        }
        file.close();
    }
    else {
        cerr << "�޷����ļ�: " << filePath << endl;
    }
    return student;
}