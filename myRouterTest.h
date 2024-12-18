#pragma once

#include "routertest.h"
#include "coursesControllerTest.h"
#include "studentsControllerTest.h"
#include "scoreByIdControllerTest.h"
#include "scoreByCourseController.h"

class MyRouter : public Router
{
public:
    virtual void setupRouting();
};
//
//void MyRouter::setupRouting()
//{
//    REGISTER_CTRL_FUN("GET", "/students", StudentsController, stuContHandle);
//    REGISTER_CTRL_FUN("GET", "/courses", CoursesController, courseContHandle);
//
//}
//
////MyRouter myRouter;