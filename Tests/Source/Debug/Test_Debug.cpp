/**
 * \file   Test_Debug.cpp
 * \brief  test Debug
 */


#include <Test/Debug/Test_Debug.h>

#include <xLib/Debug/Debug.h>
#include <xLib/Log/Trace.h>


//-------------------------------------------------------------------------------------------------
/*virtual*/
void_t
Test_Debug::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Debug::_xVERIFY_", a_caseLoops)
    {
        _xVERIFY(true);
        // _xVERIFY(false);
    }

    xTEST_CASE("Debug::xCHECK_RET", a_caseLoops)
    {
        // xCHECK_RET(expr, return_expr)
    }

    xTEST_CASE("Debug::xCHECK_DO_", a_caseLoops)
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

    xTEST_CASE("Debug::xCHECK_MSG_", a_caseLoops)
    {
        // xCHECK_MSG(expr, comment)
    }

    xTEST_CASE("Debug::xCHECK_MSG_RET_", a_caseLoops)
    {
        // xCHECK_MSG_RET(expr, comment, return_expr)
    }

    xTEST_CASE("Debug::xCHECK_MSG_DO_", a_caseLoops)
    {
        xCHECK_MSG_DO(false, xT("xxx"), int_t i = 0; ++ i;);
    }

    xTEST_CASE("Debug::xNOT_IMPLEMENTED_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xNOT_IMPLEMENTED
        #endif
    }

    xTEST_CASE("Debug::xTRACE_POINT_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTRACE_POINT;
        #endif
    }
}
//-------------------------------------------------------------------------------------------------
