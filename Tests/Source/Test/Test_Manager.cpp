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

    virtual bool_t unit() xOVERRIDE
    {
        xTEST(true);

        return true;
    }
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Manager::unit()
{
    xTEST_CASE("Manager")
    {
        cint_t    argsNum       = 5;
        ctchar_t *args[argsNum] = {xT("./xLib_test"), xT("0"), xT("1"), xT("1"), xT("1")};

        Manager manager(argsNum, args);

        Test_Simple1 unit1;
        manager.add(&unit1);

        m_bRv = manager.run();
        xTEST(m_bRv);
    }

    xTEST_CASE("ManagerData")
    {
        ManagerData data;
        Manager manager(data);

        Test_Simple1 unit1;
        manager.add(&unit1);

        m_bRv = manager.run();
        xTEST(m_bRv);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
