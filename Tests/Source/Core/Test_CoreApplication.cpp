/**
 * \file   Test_CoreApplication.cpp
 * \brief  test CoreApplication
 */


#include <Test/Core/Test_CoreApplication.h>


//-------------------------------------------------------------------------------------------------
class Failer
{
public:
    void_t bug()
    {
    #if 0
        int *p = xPTR_NULL;
        *p = 10;
    #endif

    #if 0
        throw 0;  // unhandled exception: calls terminate handler
    #endif

    #if 1
        std::vector<size_t> v;
        v.at(1);
    #endif
    }

    void_t foo1()
    {
        bug();
    }

    void_t foo2()
    {
        foo1();
    }

    void_t foo3()
    {
        foo2();
    }
};
//-------------------------------------------------------------------------------------------------
class UserApplication :
    public CoreApplication
    /// user application
{
public:
                   UserApplication(std::ctstring_t &a_appGuid, std::ctstring_t &a_locale) :
                       CoreApplication(a_appGuid, a_locale)
                   {
                       Trace() << xFUNCTION;
                   }

    virtual bool_t onRun() xOVERRIDE
    {
        Trace() << xFUNCTION;

        std::vec_tstring_t args;
        CoreApplication::args(true, &args);
        CoreApplication::isRunnig();
        CoreApplication::dirsCreate();
        bool bRv = CoreApplication::selfCheck();

        {
        #if 1
            Failer failer;
            failer.foo3();
        #endif
        }
    }

private:
    xNO_COPY_ASSIGN(UserApplication)
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_CoreApplication::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CoreApplication", a_caseLoops)
    {
        UserApplication user_application(xT("[app_name]_guid"), xT(""));
        user_application.run();
    }
}
//-------------------------------------------------------------------------------------------------
