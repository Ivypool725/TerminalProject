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

//// 替换模板中的一般性属性占位符（使用ModelAndView指针参数）
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
//                // 处理每一行中各个单元格（包括超链接内）的占位符替换
//                for (size_t j = 0; j < table->data[i].size(); ++j) {
//                    // 查找当前单元格内容中是否有占位符
//                    size_t placeholderStart = rowContent.find(a);
//                    while (placeholderStart != string::npos) {
//                        if (j == 0 && rowContent.find("<a href='/scorebystudent/") != string::npos) {
//                            // 如果是超链接中的 {{row.id}} 占位符（假设id在每行第一个数据位置）
//                            // 替换为对应表格数据中的学生id
//                            rowContent.replace(placeholderStart, a.length(), table->data[i][0]);
//                        }
//                        else {
//                            // 普通单元格中的 {{row.id}} 占位符同样替换
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
//                // 将替换好的行内容替换回原模板内容中
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
				// 构建包含实际数据的行内容
				content += table->data[i][0];  // 替换 {{row.id}} 为实际的学生id
				content += "'>";
				content += table->data[i][0];  // 显示的链接文本也用学生id
				content += "</a></td><td>";
				content += table->data[i][1];  // 替换 {{row.name}} 为实际的学生姓名
				content += "</td><td>";
				content += table->data[i][2];  // 替换 {{row.sex}} 为实际的学生性别
				content += "</td><td>";
				content += table->data[i][3];  // 替换 {{row.age}} 为实际的学生年龄
				content += "</td></tr>";
				filledRows << content;
				content = "<tr><td><a href='/scorebystudent/";  // 重置content，准备构建下一行
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
				// 构建包含实际数据的行内容
				content += table->data[i][0];  // 替换 {{row.id}} 为实际的课程id
				content += "'>";
				content += table->data[i][0];  // 显示的链接文本也用课程id
				content += "</a></td><td>";
				content += table->data[i][1];  // 替换 {{row.name}} 为实际的课程名称
				content += "</td><td>";
				content += table->data[i][2];  // 替换 {{row.teacher}} 为实际的授课教师
				content += "</td><td>";
				content += table->data[i][3];  // 替换 {{row.time}} 为实际的上课时间
				content += "</td><td>";
				content += table->data[i][4];  // 替换 {{row.location}} 为实际的上课地点
				content += "</td></tr>";
				filledRows << content;
				content = "<tr><td><a href='/scorebycourse/";  // 重置content，准备构建下一行
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

	// 处理一般性属性的占位符替换（例如 {{name}} 等，在attributes里存着对应的值）
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

	// 处理一般性属性的占位符替换（例如 {{name}} 等，在attributes里存着对应的值）
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
//			templateContent.replace(startPos, endPos - startPos + tableEndTag.length(), tableRows.str());//起始，长度，用于替换的字符串
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

//// renderStu函数定义，完成对学生相关页面模板的填充
//string View::renderStu(ModelAndView& modelAndView) 
//{
//	//string templateContent = readTemplate("students.htm");
//	
//	// 替换成绩信息表格数据占位符
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
//	// 替换学生基本属性信息占位符
//	//replaceAttributes(templateContent, modelAndView.getAttributes());
//	// 替换成绩信息表格数据占位符
//	replaceStuTableData(&modelAndView);//change!!!!!!!!!!!!!!
//	return templateContent;
//}
//
//string View::renderScoreById(ModelAndView& modelAndView) 
//{
//	string templateContent = readTemplate("scores_by_stu.htm");
//	// 替换学生基本属性信息占位符
//	replaceAttributes(&modelAndView);
//	// 替换成绩信息表格数据占位符
//	replaceStuTableData(&modelAndView);
//	return templateContent;
//}
//
//
//string View::renderScoreByCourse(ModelAndView& modelAndView) 
//{
//	string templateContent = readTemplate("scores_by_course.htm");
//	// 替换学生基本属性信息占位符
//	replaceAttributes(&modelAndView);
//	// 替换成绩信息表格数据占位符
//	replaceStuTableData(&modelAndView);
//	return templateContent;
