#include "view.h"

string View::readTemplate(const string& templateName)
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

//// �滻ģ���е�һ��������ռλ����ʹ��ModelAndViewָ�������
//void View::replaceAttributes(ModelAndView* modelAndView) {
//	const auto& attributesMap = modelAndView->getAttributes();
//	for (const auto& pair : attributesMap) {
//		string placeholder = "{{" + pair.first + "}}";
//		string templateName = modelAndView->getTemplateName();
//		string templateContent = modelAndView->readTemplate(templateName);
//		size_t pos = templateContent.find(placeholder);
//		while (pos != string::npos) {
//			templateContent.replace(pos, placeholder.length(), pair.second);
//			pos = templateContent.find(placeholder, pos + pair.second.length());
//		}
//	}
//}

//string View::replaceStuTableData(ModelAndView* modelAndView) {
//    string templateContent = readTemplate(modelAndView->getTemplateName());
//    const auto& tableDataMap = modelAndView->getTableData();
//
//    for (const auto& pair : tableDataMap) {
//        string tableStartTag = "{{each " + pair.first + " row}}";
//        string tableEndTag = "{{/each}}";
//
//        size_t startPos = templateContent.find(tableStartTag);
//        size_t endPos = templateContent.find(tableEndTag);
//
//        const auto& table = pair.second;
//        string content = "<tr><td><a href = '/scorebystudent/"+
//            //{{row.id}}'>{{row.id}}</a></td><td>{{row.name}}</td><td>{{row.sex}}</td><td>{{row.age}}</td>< /tr>";
//
//
//        if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
//            const auto& table = pair.second;
//            for (size_t i = 0; i < table->data.size(); +i++) {
//                string rowContent = templateContent.substr(startPos, endPos - startPos + tableEndTag.length());
//                string a = "{{row.id}}";
//                string b = "{{row.name}}";
//                string c = "{{row.sex}}";
//                string d = "{{row.age}}";
//
//                // ����ÿһ���и�����Ԫ�񣨰����������ڣ���ռλ���滻
//                for (size_t j = 0; j < table->data[i].size(); ++j) {
//                    // ���ҵ�ǰ��Ԫ���������Ƿ���ռλ��
//                    size_t placeholderStart = rowContent.find(a);
//                    while (placeholderStart != string::npos) {
//                        if (j == 0 && rowContent.find("<a href='/scorebystudent/") != string::npos) {
//                            // ����ǳ������е� {{row.id}} ռλ��������id��ÿ�е�һ������λ�ã�
//                            // �滻Ϊ��Ӧ��������е�ѧ��id
//                            rowContent.replace(placeholderStart, a.length(), table->data[i][0]);
//                        }
//                        else {
//                            // ��ͨ��Ԫ���е� {{row.id}} ռλ��ͬ���滻
//                            rowContent.replace(placeholderStart, a.length(), table->data[i][0]);
//                        }
//                        placeholderStart = rowContent.find(a);
//                    }
//
//                    placeholderStart = rowContent.find(b);
//                    while (placeholderStart != string::npos) {
//                        rowContent.replace(placeholderStart, b.length(), table->data[i][1]);
//                        placeholderStart = rowContent.find(b);
//                    }
//
//                    placeholderStart = rowContent.find(c);
//                    while (placeholderStart != string::npos) {
//                        rowContent.replace(placeholderStart, c.length(), table->data[i][2]);
//                        placeholderStart = rowContent.find(c);
//                    }
//
//                    placeholderStart = rowContent.find(d);
//                    while (placeholderStart != string::npos) {
//                        rowContent.replace(placeholderStart, d.length(), table->data[i][3]);
//                        placeholderStart = rowContent.find(d);
//                    }
//                }
//                // ���滻�õ��������滻��ԭģ��������
//                templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), rowContent);
//            }
//        }
//    }
//    cerr << "Data replaced.\n";
//    return templateContent;
//}

string View::replaceStuTableData(ModelAndView* modelAndView) {
	string templateContent = readTemplate(modelAndView->getTemplateName());
	const auto& tableDataMap = modelAndView->getTableData();

	for (const auto& pair : tableDataMap) {
		string tableStartTag = "{{each " + pair.first + " row}}";
		string tableEndTag = "{{/each}}";

		size_t startPos = templateContent.find(tableStartTag);
		size_t endPos = templateContent.find(tableEndTag);

		if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
			const auto& table = pair.second;
			string content = "<tr><td><a href='/scorebystudent/";
			stringstream filledRows;
			for (size_t i = 0; i < table->data.size(); ++i) {
				// ��������ʵ�����ݵ�������
				content += table->data[i][0];  // �滻 {{row.id}} Ϊʵ�ʵ�ѧ��id
				content += "'>";
				content += table->data[i][0];  // ��ʾ�������ı�Ҳ��ѧ��id
				content += "</a></td><td>";
				content += table->data[i][1];  // �滻 {{row.name}} Ϊʵ�ʵ�ѧ������
				content += "</td><td>";
				content += table->data[i][2];  // �滻 {{row.sex}} Ϊʵ�ʵ�ѧ���Ա�
				content += "</td><td>";
				content += table->data[i][3];  // �滻 {{row.age}} Ϊʵ�ʵ�ѧ������
				content += "</td></tr>";
				filledRows << content;
				content = "<tr><td><a href='/scorebystudent/";  // ����content��׼��������һ��
			}
			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), filledRows.str());
		}
	}
	cerr << "Data replaced.\n";
	return templateContent;
}

string View::replaceCourseTableData(ModelAndView* modelAndView) {
	string templateContent = readTemplate(modelAndView->getTemplateName());
	const auto& tableDataMap = modelAndView->getTableData();

	for (const auto& pair : tableDataMap) {
		string tableStartTag = "{{each " + pair.first + " row}}";
		string tableEndTag = "{{/each}}";

		size_t startPos = templateContent.find(tableStartTag);
		size_t endPos = templateContent.find(tableEndTag);

		if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
			const auto& table = pair.second;
			string content = "<tr><td><a href='/scorebycourse/";
			stringstream filledRows;
			for (size_t i = 0; i < table->data.size(); ++i) {
				// ��������ʵ�����ݵ�������
				content += table->data[i][0];  // �滻 {{row.id}} Ϊʵ�ʵĿγ�id
				content += "'>";
				content += table->data[i][0];  // ��ʾ�������ı�Ҳ�ÿγ�id
				content += "</a></td><td>";
				content += table->data[i][1];  // �滻 {{row.name}} Ϊʵ�ʵĿγ�����
				content += "</td><td>";
				content += table->data[i][2];  // �滻 {{row.teacher}} Ϊʵ�ʵ��ڿν�ʦ
				content += "</td><td>";
				content += table->data[i][3];  // �滻 {{row.time}} Ϊʵ�ʵ��Ͽ�ʱ��
				content += "</td><td>";
				content += table->data[i][4];  // �滻 {{row.location}} Ϊʵ�ʵ��Ͽεص�
				content += "</td></tr>";
				filledRows << content;
				content = "<tr><td><a href='/scorebycourse/";  // ����content��׼��������һ��
			}
			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), filledRows.str());
		}
	}
	cerr << "Data replaced.\n";
	return templateContent;
}


string View::replaceScoreById(ModelAndView* modelAndView)
{
	string templateContent = modelAndView->readTemplate(modelAndView->getTemplateName());
	const auto& tableDataMap = modelAndView->getTableData();
	const auto& attributes = modelAndView->getAttributes();

	// ����һ�������Ե�ռλ���滻������ {{name}} �ȣ���attributes����Ŷ�Ӧ��ֵ��
	for (const auto& attrPair : attributes) 
	{
		string placeholder = "{{" + attrPair.first + "}}";
		size_t placeholderPos = templateContent.find(placeholder);
		while (placeholderPos != string::npos) {
			templateContent.replace(placeholderPos, placeholder.length(), attrPair.second);
			placeholderPos = templateContent.find(placeholder);
		}
	}

	for (const auto& pair : tableDataMap) {
		string tableStartTag = "{{each " + pair.first + " row}}";
		string tableEndTag = "{{/each}}";

		size_t startPos = templateContent.find(tableStartTag);
		size_t endPos = templateContent.find(tableEndTag);

		if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
			const auto& table = pair.second;
			stringstream filledRows;
			for (size_t i = 0; i < table->data.size(); ++i) {
				string content = "<tr><td>";
				content += table->data[i][0];  // Course
				content += "</a></td><td>";
				content += table->data[i][1];  // Score
				content += "</td><td>";
				content += table->data[i][2];  // Time
				content += "</td><td>";
				content += table->data[i][3];  // Location
				content += "</td><td>";
				content += table->data[i][4];  // Teacher
				content += "</td></tr>";
				filledRows << content;
			}
			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), filledRows.str());
		}
	}
	cerr << "Data replaced.\n";
	return templateContent;
}



string View::replaceScoreByCourse(ModelAndView* modelAndView)
{
	string templateContent = modelAndView->readTemplate(modelAndView->getTemplateName());
	const auto& tableDataMap = modelAndView->getTableData();
	const auto& attributes = modelAndView->getAttributes();

	// ����һ�������Ե�ռλ���滻������ {{name}} �ȣ���attributes����Ŷ�Ӧ��ֵ��
	for (const auto& attrPair : attributes)
	{
		string placeholder = "{{" + attrPair.first + "}}";
		size_t placeholderPos = templateContent.find(placeholder);
		while (placeholderPos != string::npos) {
			templateContent.replace(placeholderPos, placeholder.length(), attrPair.second);
			placeholderPos = templateContent.find(placeholder);
		}
	}

	for (const auto& pair : tableDataMap) {
		string tableStartTag = "{{each " + pair.first + " row}}";
		string tableEndTag = "{{/each}}";

		size_t startPos = templateContent.find(tableStartTag);
		size_t endPos = templateContent.find(tableEndTag);

		if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
			const auto& table = pair.second;
			stringstream filledRows;

			for (size_t i = 0; i < table->data.size(); ++i) {
				string content = "<tr><td>";
				content += table->data[i][0];  // 
				content += "</a></td><td>";
				content += table->data[i][1];  // 
				content += "</td><td>";
				content += table->data[i][2];  // 
				content += "</td><td>";
				content += table->data[i][3];  // 
				content += "</td><td>";
				content += table->data[i][4];  // 
				content += "</td></tr>";
				filledRows << content;
			}
			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), filledRows.str());
		}
	}
	cerr << "Data replaced.\n";
	return templateContent;
}





//void View::replaceTableData(string& templateContent, unordered_map<string, shared_ptr<DataTable>> tableData)
//{
//	for (const auto& pair : tableData)
//	{
//		string tableStartTag= "{{each " + pair.first + " row}}";
//		string tableEndTag = "{{/each}}";
//		size_t startPos = templateContent.find(tableStartTag);
//		size_t endPos = templateContent.find(tableEndTag);
//		if (startPos != string::npos && startPos != string::npos)
//		{
//			stringstream tableRows;
//			const auto& table = pair.second;
//			for (size_t i = 0; i < table->data.size(); ++i)
//			{
//				tableRows << "<tr>";
//				for (size_t j = 0; j < table->data[i].size(); ++j)
//				{
//					tableRows << "<td>" << table->data[i][j] << "</td>";
//				}
//				tableRows << "</tr>";
//			}
//			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), tableRows.str());//��ʼ�����ȣ������滻���ַ���
//		}
//	}
//}
//
//string View::render(const ModelAndView& modelAndView) {
//	std::string templateContent = readTemplate(modelAndView.getTemplateName());
//	replaceAttributes(templateContent, modelAndView.getAttributes());
//	replaceTableData(templateContent, modelAndView.getTableData());
//	return templateContent;
//}

//// renderStu�������壬��ɶ�ѧ�����ҳ��ģ������
//string View::renderStu(ModelAndView& modelAndView) 
//{
//	//string templateContent = readTemplate("students.htm");
//	
//	// �滻�ɼ���Ϣ�������ռλ��
//	string templateContent=replaceStuTableData(&modelAndView);
//	return templateContent;
//}
//string StuModel = "students.htm";
//string CourseModel = "courses.htm";
//string Score_By_Stu = "scores_by_stu.htm";
//string Score_By_Course = "scores_by_course.htm";
//
//string View::renderCourse( ModelAndView& modelAndView) {
//	string templateContent = readTemplate("courses.htm");
//	// �滻ѧ������������Ϣռλ��
//	//replaceAttributes(templateContent, modelAndView.getAttributes());
//	// �滻�ɼ���Ϣ�������ռλ��
//	replaceStuTableData(&modelAndView);//change!!!!!!!!!!!!!!
//	return templateContent;
//}
//
//string View::renderScoreById(ModelAndView& modelAndView) 
//{
//	string templateContent = readTemplate("scores_by_stu.htm");
//	// �滻ѧ������������Ϣռλ��
//	replaceAttributes(&modelAndView);
//	// �滻�ɼ���Ϣ�������ռλ��
//	replaceStuTableData(&modelAndView);
//	return templateContent;
//}
//
//
//string View::renderScoreByCourse(ModelAndView& modelAndView) 
//{
//	string templateContent = readTemplate("scores_by_course.htm");
//	// �滻ѧ������������Ϣռλ��
//	replaceAttributes(&modelAndView);
//	// �滻�ɼ���Ϣ�������ռλ��
//	replaceStuTableData(&modelAndView);
//	return templateContent;
