/**
 * \file   CxTest_xDebug.cpp
 * \brief  test xDebug
 */


#include <Test/Debug/CxTest_xDebug.h>

#include <xLib/Debug/xDebug.h>


//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_xDebug::unit(
    culonglong_t &a_caseLoops
)
{
    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xTEST_*_", a_caseLoops)
    {
        {
            int_t iSimpleVar = 1;
            int_t iVeryVerySimpleVar = 1;
            xTEST_MSG_EQ(iSimpleVar, iVeryVerySimpleVar, xT("Simple message"));

            xTEST_EQ(1UL, 1UL);
        }

        {
            xTEST_DIFF(1UL, 0UL);
        }

        {
            xTEST_LESS(0UL, 1UL);
        }

        {
            xTEST_GR(1UL, 0UL);
        }

        {
            xTEST_LESS_EQ(1UL, 2UL);
            xTEST_LESS_EQ(2UL, 2UL);
        }

        {
            xTEST_GR_EQ(2UL, 1UL);
            xTEST_GR_EQ(2UL, 2UL);
        }

        {
            long_t *pliVal = new long_t;

            xTEST_PTR(pliVal);

            xPTR_DELETE(pliVal);
        }

        {
            long_t *pliVal = NULL;
            xTEST_PTR_FAIL(pliVal);
        }

        {
            #if xTEST_IGNORE
                xTEST_FAIL;
            #endif
        }

        {
            xTEST(true);

            #if xTEST_IGNORE
                xTEST(false);
            #endif
        }
    }

    //--------------------------------------------------
    //  ...
    xTEST_CASE("xDebug::xTEST_MSG_*_", a_caseLoops)
    {

    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xSTD_VERIFY_", a_caseLoops)
    {
        xSTD_VERIFY(true);
        // xSTD_VERIFY(false);
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xCHECK_RET", a_caseLoops)
    {
        // xCHECK_RET(expr, return_expr)
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xCHECK_DO_", a_caseLoops)
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

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xCHECK_MSG_", a_caseLoops)
    {
        // xCHECK_MSG(expr, comment)
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xCHECK_MSG_RET_", a_caseLoops)
    {
        // xCHECK_MSG_RET(expr, comment, return_expr)
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xCHECK_MSG_DO_", a_caseLoops)
    {
        xCHECK_MSG_DO(false, xT("xxx"), int_t i = 0; ++ i;);
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xTEST_STATIC_", a_caseLoops)
    {
        xTEST_STATIC(true);

        #if xTEST_IGNORE && 0
            xTEST_STATIC(false);
        #endif
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xNOT_IMPLEMENTED_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xNOT_IMPLEMENTED;
        #endif
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xTRACE_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTRACE(xT("test_data"));
        #endif
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xTRACEV_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTRACEV(xT("%s: %d"), xT("test_data"), 10);
        #endif
    }

    //--------------------------------------------------
    //
    xTEST_CASE("xDebug::xTRACE_POINT_", a_caseLoops)
    {
        #if xTEST_IGNORE
            xTRACE_POINT;
        #endif
    }
}
//------------------------------------------------------------------------------
