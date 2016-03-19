/**
 * \file   Test_Manager.cpp
 * \brief
 */


#include <Test/Test/Test_Manager.h>

#include <Test/Test_xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Manager)
//-------------------------------------------------------------------------------------------------
class Test_Simple1 :
    public Unit
    ///< tests for Simple1
{
public:
                   Test_Simple1() {}

    virtual void_t unit(std::csize_t &caseLoops) xOVERRIDE
    {
        xTEST(true);
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Manager::unit(
    std::csize_t &a_caseLoops
)
{
    xTEST_CASE("Manager", a_caseLoops)
    {
        cint_t    argsNum       = 5;
        ctchar_t *args[argsNum] = {"./xLib_test", "1", "1", "1", "1"};

        Manager manager(argsNum, args);
        manager.add(new Test_Simple1);
        manager.run();
    }

    xTEST_CASE("ManagerData", a_caseLoops)
    {
        ManagerData data;

        Manager manager(data);
        manager.add(new Test_Simple1);

        manager.run();
    }
}
//-------------------------------------------------------------------------------------------------
