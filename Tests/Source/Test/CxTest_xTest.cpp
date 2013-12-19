/**
 * \file   CxTest_xTest.cpp
 * \brief  test xTest
 */


#include <Test/Test/CxTest_xTest.h>


//---------------------------------------------------------------------------
/* virtual */
void_t
CxTest_xTest::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("xDebug::xTEST_*_", a_caseLoops)
    {
        xTEST_EQ(1UL, 1UL);
        xTEST_DIFF(1UL, 0UL);
        xTEST_LESS(0UL, 1UL);
        xTEST_GR(1UL, 0UL);
        xTEST_LESS_EQ(1UL, 2UL);
        xTEST_LESS_EQ(2UL, 2UL);
        xTEST_GR_EQ(2UL, 1UL);
        xTEST_GR_EQ(2UL, 2UL);
        xTEST_PTR(123);
        xTEST_PTR_FAIL(NULL);
    #if xTEST_IGNORE
        xTEST_FAIL;
        xTEST(false);
    #endif
        xTEST(true);
    }

    xTEST_CASE("xDebug::xTEST_MSG_*_", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_MSG_EQ(1UL, 1UL, msg);
        xTEST_MSG_DIFF(1UL, 0UL, msg);
        xTEST_MSG_LESS(0UL, 1UL, msg);
        xTEST_MSG_GR(1UL, 0UL, msg);
        xTEST_MSG_LESS_EQ(1UL, 2UL, msg);
        xTEST_MSG_LESS_EQ(2UL, 2UL, msg);
        xTEST_MSG_GR_EQ(2UL, 1UL, msg);
        xTEST_MSG_GR_EQ(2UL, 2UL, msg);
        xTEST_MSG_PTR(61466, msg);
        xTEST_MSG_PTR_FAIL(NULL, msg);
    #if xTEST_IGNORE
        xTEST_MSG_FAIL(msg);
        xTEST_MSG(false, msg);
    #endif
        xTEST_MSG(true, msg);
    }

    xTEST_CASE("xDebug::xTEST_THROWS...", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_THROWS(msg.at(msg.size() + 10), std::exception);
        xTEST_MSG_THROWS(msg.at(msg.size() + 10), std::exception, msg);

        xTEST_THROWS_ANYTHING(msg.at(msg.size() + 10));
        xTEST_MSG_THROWS_ANYTHING(msg.at(msg.size() + 10), msg);

        xTEST_THROWS_NOTHING(msg.at(0));
        xTEST_MSG_THROWS_NOTHING(msg.at(0), msg);
    }

    xTEST_CASE("xDebug::xTEST_NA", a_caseLoops)
    {
        size_t value = 0;
        xUNUSED(value);
        xTEST_NA(value);
        xTESTS_NA;
    }

    xTEST_CASE("xDebug::xTEST_STATIC", a_caseLoops)
    {
        xTEST_STATIC(true);

    #if xTEST_IGNORE && 0
        xTEST_STATIC(false);
    #endif
    }
}
//---------------------------------------------------------------------------
