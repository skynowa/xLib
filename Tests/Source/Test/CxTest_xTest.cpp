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

    xTEST_CASE("xDebug::xTEST_MSG_*_", a_caseLoops)
    {

    }

    xTEST_CASE("xDebug::xTEST_STATIC_", a_caseLoops)
    {
        xTEST_STATIC(true);

        #if xTEST_IGNORE && 0
            xTEST_STATIC(false);
        #endif
    }
}
//---------------------------------------------------------------------------
