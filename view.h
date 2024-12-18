#pragma once
#include<iostream>
#include<unordered_map>
#include "modelAndView.h"
#include<fstream>
#include<sstream>


using namespace std;

class View
{
public:
	string readTemplate(const string&);

	string replaceStuTableData(ModelAndView* modelAndView);
	string replaceCourseTableData(ModelAndView* modelAndView);

	string replaceScoreById(ModelAndView* modelAndView);
	string replaceScoreByCourse(ModelAndView* modelAndView);
};