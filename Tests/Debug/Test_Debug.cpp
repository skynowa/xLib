/**
 * \file   Test_Debug.cpp
 * \brief  test Debug
 */


#include "Test_Debug.h"

#include <xLib/Debug/Debug.h>
#include <xLib/Log/Trace.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Debug)
//-------------------------------------------------------------------------------------------------
/*virtual*/
bool_t
Test_Debug::unit()
{
    xTEST_CASE("xCHECK_RET")
    {
        // xCHECK_RET(expr, return_expr)
    }

    xTEST_CASE("xCHECK_DO")
    {
        class STest {
            public:
                culong_t culVal0;
                culong_t culVal1;
                culong_t culVal2;
                culong_t culVal3;

                STest() :
                    culVal0(0UL),
                    culVal1(1UL),
                    culVal2(2UL),
                    culVal3(3UL)
                {
                }

                long_t exec(cbool_t &cbFlag) {
                    if (cbFlag) {
                        xCHECK_DO(!cbFlag, return culVal0; );
                        xCHECK_DO( cbFlag, return culVal1; );
                    } else {
                        xCHECK_DO( cbFlag, return culVal2; );
                        xCHECK_DO(!cbFlag, return culVal3; );
                    }

                    return culVal0;
                }
        };

        STest t;

        m_ulRv = t.exec(true);
        xTEST_EQ(t.culVal1, m_ulRv);

        m_ulRv = t.exec(false);
        xTEST_EQ(t.culVal3, m_ulRv);
    }

    xTEST_CASE("xCHECK_MSG")
    {
        // xCHECK_MSG(expr, comment)
    }

    xTEST_CASE("xCHECK_MSG_RET")
    {
        // xCHECK_MSG_RET(expr, comment, return_expr)
    }

    xTEST_CASE("xCHECK_MSG_DO")
    {
        xCHECK_MSG_DO(false, xT("xxx"), int_t i = 0; ++ i;);
    }

    xTEST_CASE("xNOT_IMPLEMENTED")
    {
        #if xTEST_IGNORE
            xNOT_IMPLEMENTED
        #endif
    }

    xTEST_CASE("xTRACE_POINT")
    {
        #if xTEST_IGNORE
            xTRACE_POINT;
        #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
