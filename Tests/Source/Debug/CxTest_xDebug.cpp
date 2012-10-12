/**
 * \file   CxTest_xDebug.cpp
 * \brief  test xDebug
 */


#include <Test/Debug/CxTest_xDebug.h>

#include <xLib/Debug/xDebug.h>


//---------------------------------------------------------------------------
CxTest_xDebug::CxTest_xDebug() {

}
//---------------------------------------------------------------------------
CxTest_xDebug::~CxTest_xDebug() {

}
//---------------------------------------------------------------------------
/*virtual*/
void
CxTest_xDebug::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTEST_*_, cullCaseLoops)
    {
        {
            int iVal1 = 1;
            int iVal2 = 1;
            xTEST_MSG_EQ(iVal1, iVal2, "Simple message");

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
    xTEST_CASE(xDebug::xTEST_MSG_*_, cullCaseLoops)
    {

    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xSTD_VERIFY_, cullCaseLoops)
    {
        xSTD_VERIFY(true);
        // xSTD_VERIFY(false);
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xCHECK_RET, cullCaseLoops)
    {
        // xCHECK_RET(expr, return_expr)
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xCHECK_DO_, cullCaseLoops)
    {
        class STest {
            public:
                const ulong_t culVal0;
                const ulong_t culVal1;
                const ulong_t culVal2;
                const ulong_t culVal3;

                STest() :
                    culVal0(0UL),
                    culVal1(1UL),
                    culVal2(2UL),
                    culVal3(3UL)
                {
                }

                long_t exec(const bool &cbFlag) {
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
    xTEST_CASE(xDebug::xCHECK_MSG_, cullCaseLoops)
    {
        // xCHECK_MSG(expr, comment)
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xCHECK_MSG_RET_, cullCaseLoops)
    {
        // xCHECK_MSG_RET(expr, comment, return_expr)
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xCHECK_MSG_DO_, cullCaseLoops)
    {
        xCHECK_MSG_DO(false, xT("xxx"), int i = 0; ++ i;);
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTEST_STATIC_, cullCaseLoops)
    {
        xTEST_STATIC(true);

        #if xTEST_IGNORE && 0
            xTEST_STATIC(false);
        #endif
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xNOT_IMPLEMENTED_, cullCaseLoops)
    {
        #if xTEST_IGNORE
            xNOT_IMPLEMENTED;
        #endif
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTEST_CASE_, cullCaseLoops)
    {
        xTEST_CASE(case_name, 3U) {
            int iVal = 0; ++ iVal;
        }
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTRACE_, cullCaseLoops)
    {
        #if xTEST_IGNORE
            xTRACE(xT("test_data"));
        #endif
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTRACEV_, cullCaseLoops)
    {
        #if xTEST_IGNORE
            xTRACEV(xT("%s: %d"), xT("test_data"), 10);
        #endif
    }

    //--------------------------------------------------
    // 
    xTEST_CASE(xDebug::xTRACE_POINT_, cullCaseLoops)
    {
        #if xTEST_IGNORE
            xTRACE_POINT;
        #endif
    }
}
//---------------------------------------------------------------------------
