/**
 * \file  Test_xTest.cpp
 * \brief test Test
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_xTest)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_xTest::unit()
{
    xTEST_CASE("xTEST_...")
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

        auto *msgPtr = &msg;
        xTEST_PTR(msgPtr);
        xTEST_PTR_MSG(msgPtr, msg);

        std::ctstring_t *nullPtr {};
        xTEST_PTR_FAIL(nullPtr);
        xTEST_PTR_FAIL_MSG(nullPtr, msg);

    #if xTEST_IGNORE
        xTEST_FAIL;
        xTEST_FAIL_MSG(msg);

        xTEST(false);
        xTEST_MSG(false, msg);
    #endif

        xTEST(true);
        xTEST_MSG(true, msg)
    }

    xTEST_CASE("xTEST_THROW_...")
    {
        std::ctstring_t msg = xT("Simple message");

    #if xCOMPILER_MS
        #pragma warning (push)
        #pragma warning (disable: 4834) // discarding return value of function with 'nodiscard' attribute
    #endif

        xTEST_THROW(msg.at(msg.size() + 10), std::exception);
        xTEST_THROW_MSG(msg.at(msg.size() + 10), std::exception, msg);

        xTEST_THROW_ALL(msg.at(msg.size() + 10));
        xTEST_THROW_ALL_MSG(msg.at(msg.size() + 10), msg);

        xTEST_THROW_NO(msg.at(0));
        xTEST_THROW_NO_MSG(msg.at(0), msg);

    #if xCOMPILER_MS
        #pragma warning (pop)
    #endif
    }

    xTEST_CASE("xTEST_NA")
    {
        xTEST_NA(1978);
        xTESTS_NA;
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
