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

    virtual void_t unit(culonglong_t &caseLoops) xOVERRIDE
    {
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Manager::unit(
    culonglong_t &a_caseLoops
)
{
    tchar_t *args[]  = {"./xLib_test", "1", "1", "1"};
    int_t    argsNum = 4;

    cbool_t      isUseTracing = true;
    culonglong_t allLoops     = 1ULL;
    culonglong_t unitLoops    = 1ULL;
    culonglong_t caseLoops    = 1ULL;

    // add and run tests
    Manager manager(argsNum, args, isUseTracing);
    manager.add(new Test_Simple1);

    manager.run(allLoops, unitLoops, caseLoops);
}
//-------------------------------------------------------------------------------------------------
