/**
 * \file   Test_Test.cpp
 * \brief  test Test
 */


#include <Test/Test/Test_Test.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Test::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("xTEST_...", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_EQ(1UL, 1UL);
        xTEST_EQ_MSG(1UL, 1UL, msg);

        xTEST_DIFF(1UL, 0UL);
        xTEST_DIFF_MSG(1UL, 0UL, msg);

        xTEST_LESS(0UL, 1UL);
        xTEST_LESS_MSG(0UL, 1UL, msg);

        xTEST_GR(1UL, 0UL);
        xTEST_GR_MSG(1UL, 0UL, msg);

        xTEST_LESS_EQ(1UL, 2UL);
        xTEST_LESS_EQ(2UL, 2UL);
        xTEST_LESS_EQ_MSG(1UL, 2UL, msg);
        xTEST_LESS_EQ_MSG(2UL, 2UL, msg);

        xTEST_GR_EQ(2UL, 1UL);
        xTEST_GR_EQ(2UL, 2UL);
        xTEST_GR_EQ_MSG(2UL, 1UL, msg);
        xTEST_GR_EQ_MSG(2UL, 2UL, msg);

        xTEST_PTR(123);
        xTEST_PTR_MSG(61466, msg);

        xTEST_PTR_FAIL(xPTR_NULL);
        xTEST_PTR_FAIL_MSG(xPTR_NULL, msg);

    #if xTEST_IGNORE
        xTEST_FAIL;
        xTEST_FAIL_MSG(msg);

        xTEST(false);
        xTEST_MSG(false, msg);
    #endif

        xTEST(true);
        xTEST_MSG(true, msg)
    }

    xTEST_CASE("xTEST_THROW_...", a_caseLoops)
    {
        std::ctstring_t msg = xT("Simple message");

        xTEST_THROW(msg.at(msg.size() + 10), std::exception);
        xTEST_THROW_MSG(msg.at(msg.size() + 10), std::exception, msg);

        xTEST_THROW_ALL(msg.at(msg.size() + 10));
        xTEST_THROW_ALL_MSG(msg.at(msg.size() + 10), msg);

        xTEST_THROW_NO(msg.at(0));
        xTEST_THROW_NO_MSG(msg.at(0), msg);
    }

    xTEST_CASE("xTEST_NA", a_caseLoops)
    {
        xTEST_NA(1978);
        xTESTS_NA;
    }

    xTEST_CASE("xTEST_STATIC", a_caseLoops)
    {
        xTEST_STATIC(true);

    #if xTEST_IGNORE
        xTEST_STATIC(false);
    #endif
    }

    xTEST_CASE("xVERIFY", a_caseLoops)
    {
        _xVERIFY(true);
        // _xVERIFY(false);
    }
}
//-------------------------------------------------------------------------------------------------
