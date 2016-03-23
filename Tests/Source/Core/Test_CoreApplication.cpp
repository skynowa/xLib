/**
 * \file   Test_CoreApplication.cpp
 * \brief  test CoreApplication
 */


#include <Test/Core/Test_CoreApplication.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_CoreApplication)
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
                  }

    virtual int_t onRun() xOVERRIDE
    {
        std::vec_tstring_t args;
        CoreApplication::args(true, &args);
        CoreApplication::isRunnig();
        CoreApplication::dirsCreate();
        bool bRv = CoreApplication::selfCheck();

        {
        #if 0
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
bool_t
Test_CoreApplication::unit()
{
    xTEST_CASE("CoreApplication")
    {
        UserApplication userApp(xT("[app_name]_guid"), xT(""));
        userApp.run();
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
