#include "ModelAndView.h"

void ModelAndView::setTemplateName(const string& t)
{
	cerr << "set template suceeded.\n";
	templateName = t;
}

void ModelAndView::addStudentAttribute(int id)
{
	StudentsService s;
	Student student = s.getStudent(id);
	attributes["id"] = to_string(student.id);
	attributes["name"] = student.name;
	attributes["sex"] = student.sex;
	attributes["age"] = to_string(student.age);
}

void ModelAndView::addCourseAttribute(int courseId)
{
	CoursesService c;
	Course course = c.getCourseByCourseId(courseId);
	attributes["id"] = to_string(course.id);
	attributes["name"] = course.name;
	attributes["time"] = course.time;
	attributes["location"] = course.location;
	attributes["teacher"] = course.teacher;

}

string ModelAndView::getTemplateName() const 
{
	return templateName;
}

string ModelAndView::readTemplate(const string& templateName)
{
	ifstream file(templateName);
	//ifstream file("students.htm");
	if (file.is_open())
	{
		stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
	return "";
}

unordered_map<string, string> ModelAndView::getAttributes() const 
{
	return attributes;
}

unordered_map<string, shared_ptr<DataTable>> ModelAndView::getTableData() const 
{
	return tableData;
}


void ModelAndView::addTableData(const string& key, const string& serviceType, const int id) {
	shared_ptr<DataTable> table = make_shared<DataTable>();
	if (serviceType == "StudentService")
	{
		StudentsService studentservice;
		vector<Student> students = studentservice.getAllStudents();
		table->columnName = { "ID", "Name", "Sex","Age"};
		for (const Student& student : students) 
		{
			vector<string> rowData;
			rowData.push_back(to_string(student.id));
			rowData.push_back(student.name);
			rowData.push_back(student.sex);
			rowData.push_back(to_string(student.age));

			table->data.push_back(rowData);
		}

	}
	if (serviceType == "CourseService")
	{
		CoursesService courseservice;
		vector<Course> courses = courseservice.getAllCourses();
		table->columnName = { "ID", "Name", "Teacher","Time","Location" };
		for (const Course& course : courses)
		{
			vector<string> rowData;
			rowData.push_back(to_string(course.id));
			rowData.push_back(course.name);
			rowData.push_back(course.teacher);
			rowData.push_back(course.time);
			rowData.push_back(course.location);

			table->data.push_back(rowData);
		}

	}
	if (serviceType == "ScoreByIdService") {
		ScoreService scoreService;
		vector<Score> scores = scoreService.getStudentScoresById(id);  
		
		// 设置表格列名
		table->columnName = { "Course", "Score", "Time","Location","Teacher"};
		for (const Score& score : scores) {
			CoursesService courseservice;
			//vector<Course> c = courseservice.getCourseByStuId(id);
			Course c = courseservice.getCourseByCourseId(score.course_id);
			
			vector<string> rowData;
			rowData.push_back(to_string(score.course_id));
			rowData.push_back(to_string(score.score));
			rowData.push_back(c.time);
			rowData.push_back(c.location);
			rowData.push_back(c.teacher);

			table->data.push_back(rowData);
		}
	}
	if (serviceType == "ScoreByCourseService") {
		ScoreService scoreService;
		vector<Score> scores = scoreService.getCourseScoresById(id);//stuid,score

		// 设置表格列名
		table->columnName = { "Student ID", "Name", "Score","Age","Sex" };
		for (const Score& c : scores) {
			StudentsService studentservice;
			Student s = studentservice.getStudent(c.stu_id);

			vector<string> rowData;
			rowData.push_back(to_string(c.stu_id));
			rowData.push_back(s.name);
			rowData.push_back(to_string(c.score));
			rowData.push_back(to_string(s.age));
			rowData.push_back(s.sex);

			table->data.push_back(rowData);
		}
	}
	
	cerr << "Data added.\n";
	tableData[key] = table;
}
