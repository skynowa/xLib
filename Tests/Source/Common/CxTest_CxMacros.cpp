/**
 * \file   CxTest_CxMacros.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxMacros.h>


//---------------------------------------------------------------------------
CxTest_CxMacros::CxTest_CxMacros() {

}
//---------------------------------------------------------------------------
CxTest_CxMacros::~CxTest_CxMacros() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxMacros::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    // several combinations of preprocessor's defines
    xTEST_CASE(cullCaseLoops)
    {
        /*
            if (DEFINE_VAL == NOT_ZERO_DIGIT) {
                [true]
            } else {
                [false]
            }
        */

        {
            #define xDEF_A


            #if defined(xDEF_A)

            #else
                xTEST_FAIL;
            #endif

            //#if xDEF_A                      //compile error: #if with no expression
            //
            //#endif

            //#if defined(xDEF_A) && xDEF_A   //compile error: operator '&&' has no right operand
            //
            //#endif
        }

        {
            #define xDEF_B -1


            #if defined(xDEF_B) && xDEF_B

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_C 0


            #if defined(xDEF_C) && xDEF_C
                xTEST_FAIL;
            #else

            #endif
        }

        {
            #define xDEF_D 1


            #if defined(xDEF_D) && xDEF_D

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_E 2


            #if defined(xDEF_E) && xDEF_E

            #else
                xTEST_FAIL;
            #endif
        }

        {
            #define xDEF_F zzz


            #if defined(xDEF_F) && xDEF_F
                xTEST_FAIL;
            #else

            #endif
        }
    }

    //-------------------------------------
    // xPTR_DELETE
    xTEST_CASE(cullCaseLoops)
    {
        int *pPtr = new int();
        xTEST_PTR(pPtr);

        /*CxMacros::*/xPTR_DELETE(pPtr);
        xASSERT(NULL == pPtr);
    }

    //-------------------------------------
    // xARRAY_DELETE
    xTEST_CASE(cullCaseLoops)
    {
        int *pPtr = new int[5];
        xTEST_PTR(pPtr);

        /*CxMacros::*/xARRAY_DELETE(pPtr);
        xASSERT(NULL == pPtr);
    }

    //-------------------------------------
    // xBUFF_ZERO
    xTEST_CASE(cullCaseLoops)
    {
        tchar_t szBuff[255 + 1];

        xBUFF_ZERO(szBuff);

        for (size_t i = 0; i < xARRAY_SIZE(szBuff); ++ i) {
            xTEST_EQ(xT('\0'), szBuff[i]);
        }
    }

    //-------------------------------------
    // xARRAY_SIZE
    xTEST_CASE(cullCaseLoops)
    {
        {
            tchar_t szBuff[256] = {0};
            m_uiRv = xARRAY_SIZE(szBuff);
            xTEST_EQ(256U, m_uiRv);

            int aiBuff[256] = {0};
            m_uiRv = xARRAY_SIZE(aiBuff);
            xTEST_EQ(256U, m_uiRv);

            std::tstring_t asBuff[256];
            m_uiRv = xARRAY_SIZE(asBuff);
            xTEST_EQ(256U, m_uiRv);
        }

        //must compile-error
        {
            ////tchar_t *pszBuff = NULL;
            ////m_uiRv = xARRAY_SIZE(pszBuff);
        }
    }

    //-------------------------------------
    // xMAX
    xTEST_CASE(cullCaseLoops)
    {
        m_uiRv = xMAX(0, 1);
        xTEST_EQ(1U, m_uiRv);
    }

    //-------------------------------------
    // xMIN
    xTEST_CASE(cullCaseLoops)
    {
        m_uiRv = xMIN(5, 8);
        xTEST_EQ(5U, m_uiRv);
    }

    //-------------------------------------
    // xUNUSED
    xTEST_CASE(cullCaseLoops)
    {
        size_t uiArg = 0;

        xUNUSED(uiArg);
    }

    //-------------------------------------
    // xLEX_TO_STR
    xTEST_CASE(cullCaseLoops)
    {
        long_t liVal = - 1;

        m_sRv = xLEX_TO_STR(liVal);
        xTEST_EQ(std::tstring_t(xT("liVal")), m_sRv);

        xUNUSED(liVal);
    }

    //-------------------------------------
    // xLEX_CAT
    xTEST_CASE(cullCaseLoops)
    {
        std::string sVal;

        xLEX_CAT(s, Val) = xT("XLIB_VAL");
        xTEST_EQ(std::tstring_t(xT("XLIB_VAL")), sVal);

        sVal.clear();
    }

    //-------------------------------------
    // xS2US
    xTEST_CASE(cullCaseLoops)
    {
    }

    //-------------------------------------
    // xUS2S
    xTEST_CASE(cullCaseLoops)
    {
    }

    //-------------------------------------
    // xS2TS
    xTEST_CASE(cullCaseLoops)
    {
    }

    //-------------------------------------
    // xTS2S
    xTEST_CASE(cullCaseLoops)
    {
    }

    //-------------------------------------
    // dRound
    xTEST_CASE(cullCaseLoops)
    {
        const double cdData[][2] = {
            {10.5,   11.0},
            {10.0,   10.0},
            {10.4,   10.0},
            {0.0,    0.0},
            {-10.4, -10.0},
            //TODO: {-10.5, -11.0},
            {-10.6, -11.0}
        };

        for (size_t i = 0; i < xARRAY_SIZE(cdData); ++ i) {
            double dRes0 = CxMacros::round(cdData[i][0]);
            double dRes1 = cdData[i][1];
            xTEST_EQ(dRes0, dRes1);
        }
    }

    //-------------------------------------
    // qualifiers
    xTEST_CASE(cullCaseLoops)
    {
        // xPR_SIZET
        {
            const size_t cuiValue = 2356567;

            m_sRv = CxString::sFormat(xT("%")xPR_SIZET, cuiValue);
            xTEST_EQ(CxString::lexical_cast(cuiValue), m_sRv);
        }

        // xPR_I64d
        {
            const longlong_t cllValue = 36745723;

            m_sRv = CxString::sFormat(xT("%")xPR_I64d, cllValue);
            xTEST_EQ(CxString::lexical_cast(cllValue), m_sRv);
        }

        // xPR_I64u
        {
            const ulonglong_t cullValue = 4767834;

            m_sRv = CxString::sFormat(xT("%")xPR_I64u, cullValue);
            xTEST_EQ(CxString::lexical_cast(cullValue), m_sRv);
        }

        // xPR_I64x
        {
            const longlong_t cllValue = 57830;

            m_sRv = CxString::sFormat(xT("%")xPR_I64x, cllValue);
            xTEST_EQ(CxString::sToLowerCase( CxString::lexical_cast(cllValue, 16) ), m_sRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
