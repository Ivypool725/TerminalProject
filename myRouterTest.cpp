#include "myRouterTest.h"


void MyRouter::setupRouting()
{
    REGISTER_CTRL_FUN("GET", "/students", StudentsController, stuContHandle);
    REGISTER_CTRL_FUN("GET", "/courses", CoursesController, courseContHandle);
    REGISTER_CTRL_FUN("GET", "/scores_by_stu", ScoreByIdController, scoreByIdContHandle);
    REGISTER_CTRL_FUN("GET", "/scores_by_course", ScoreByCourseController, scoreByCourseContHandle);

}

//MyRouter myRouter;
