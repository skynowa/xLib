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
    xTEST_CASE("xDebug::xTEST_...", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_EQ(1UL, 1UL);
        xTEST_MSG_EQ(1UL, 1UL, msg);

        xTEST_DIFF(1UL, 0UL);
        xTEST_MSG_DIFF(1UL, 0UL, msg);

        xTEST_LESS(0UL, 1UL);
        xTEST_MSG_LESS(0UL, 1UL, msg);

        xTEST_GR(1UL, 0UL);
        xTEST_MSG_GR(1UL, 0UL, msg);

        xTEST_LESS_EQ(1UL, 2UL);
        xTEST_LESS_EQ(2UL, 2UL);
        xTEST_MSG_LESS_EQ(1UL, 2UL, msg);
        xTEST_MSG_LESS_EQ(2UL, 2UL, msg);

        xTEST_GR_EQ(2UL, 1UL);
        xTEST_GR_EQ(2UL, 2UL);
        xTEST_MSG_GR_EQ(2UL, 1UL, msg);
        xTEST_MSG_GR_EQ(2UL, 2UL, msg);

        xTEST_PTR(123);
        xTEST_MSG_PTR(61466, msg);

        xTEST_PTR_FAIL(NULL);
        xTEST_MSG_PTR_FAIL(NULL, msg);

    #if xTEST_IGNORE
        xTEST_FAIL;
        xTEST_MSG_FAIL(msg);

        xTEST(false);
        xTEST_MSG(false, msg);
    #endif

        xTEST(true);
        xTEST_MSG(true, msg)
    }

    xTEST_CASE("xDebug::xTEST_THROW_...", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_THROW(msg.at(msg.size() + 10), std::exception);
        xTEST_MSG_THROW(msg.at(msg.size() + 10), std::exception, msg);

        xTEST_THROW_ALL(msg.at(msg.size() + 10));
        xTEST_MSG_THROW_ALL(msg.at(msg.size() + 10), msg);

        xTEST_THROW_NO(msg.at(0));
        xTEST_MSG_THROW_NO(msg.at(0), msg);
    }

    xTEST_CASE("xDebug::xTEST_NA", a_caseLoops)
    {
        xTEST_NA(1978);
        xTESTS_NA;
    }

    xTEST_CASE("xDebug::xTEST_STATIC", a_caseLoops)
    {
        xTEST_STATIC(true);

    #if xTEST_IGNORE
        xTEST_STATIC(false);
    #endif
    }
}
//---------------------------------------------------------------------------
