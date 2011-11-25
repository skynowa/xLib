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
    const ulonglong_t cullBlockLoops
)
{
    //--------------------------------------------------
    //several combinations of preprocessor's defines
    xTEST_CASE(cullBlockLoops)
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
    //xPTR_DELETE
    xTEST_CASE(cullBlockLoops)
    {
        int *pPtr = new int();
        xTEST_PTR(pPtr);

        /*CxMacros::*/xPTR_DELETE(pPtr);
        xASSERT(NULL == pPtr);
    }

    //-------------------------------------
    //xARRAY_DELETE
    xTEST_CASE(cullBlockLoops)
    {
        int *pPtr = new int[5];
        xTEST_PTR(pPtr);

        /*CxMacros::*/xARRAY_DELETE(pPtr);
        xASSERT(NULL == pPtr);
    }

    //-------------------------------------
    //xBUFF_ZERO
    xTEST_CASE(cullBlockLoops)
    {
        tchar_t szBuff[255 + 1];

        xBUFF_ZERO(szBuff);

        for (size_t i = 0; i < xARRAY_SIZE(szBuff); ++ i) {
            xTEST_EQ(xT('\0'), szBuff[i]);
        }
    }

    //-------------------------------------
    //xARRAY_SIZE
    xTEST_CASE(cullBlockLoops)
    {
        {
            tchar_t szBuff[256] = {0};
            m_uiRes = xARRAY_SIZE(szBuff);
            xTEST_EQ(256U, m_uiRes);

            int aiBuff[256] = {0};
            m_uiRes = xARRAY_SIZE(aiBuff);
            xTEST_EQ(256U, m_uiRes);

            std::tstring_t asBuff[256];
            m_uiRes = xARRAY_SIZE(asBuff);
            xTEST_EQ(256U, m_uiRes);
        }

        //must compile-error
        {
            ////tchar_t *pszBuff = NULL;
            ////m_uiRes = xARRAY_SIZE(pszBuff);
        }
    }

    //-------------------------------------
    //xMAX
    xTEST_CASE(cullBlockLoops)
    {
        m_uiRes = xMAX(0, 1);
        xTEST_EQ(1U, m_uiRes);
    }

    //-------------------------------------
    //xMIN
    xTEST_CASE(cullBlockLoops)
    {
        m_uiRes = xMIN(5, 8);
        xTEST_EQ(5U, m_uiRes);
    }
    //-------------------------------------
    //xUNUSED
    xTEST_CASE(cullBlockLoops)
    {
        size_t uiArg = 0;

        xUNUSED(uiArg);
    }

    //-------------------------------------
    //xS2US
    xTEST_CASE(cullBlockLoops)
    {
    }

    //-------------------------------------
    //xUS2S
    xTEST_CASE(cullBlockLoops)
    {
    }

    //-------------------------------------
    //xS2TS
    xTEST_CASE(cullBlockLoops)
    {
    }

    //-------------------------------------
    //xTS2S
    xTEST_CASE(cullBlockLoops)
    {
    }

    //-------------------------------------
    //xAsTString
    xTEST_CASE(cullBlockLoops)
    {
        //1
        {
            const tchar_t *pcszBuff = xT("xxxxx");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xTEST_EQ(std::tstring_t(pcszBuff), m_sRes);
        }

        //2
        {
            const tchar_t *pcszBuff = xT("1236cnqwieru872692*qwer8lkl;l<l;hoihljkhlwcruqw");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xTEST_EQ(std::tstring_t(pcszBuff), m_sRes);
        }

        //3
        {
            const tchar_t *pcszBuff = xT("/n/n/n/n/n/n/n/t/t/t/t/t/t");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xTEST_EQ(std::tstring_t(pcszBuff), m_sRes);
        }

        //4
        {
            const tchar_t *pcszBuff = xT("");

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xTEST_EQ(std::tstring_t(pcszBuff), m_sRes);
        }

        //5
        {
            const tchar_t *pcszBuff = NULL;

            m_sRes = CxMacros::sAsTString(pcszBuff);
            xTEST_EQ(std::tstring_t(), m_sRes);
        }

        //7
        {
            const tchar_t cszBuff[] = xT("sdjkrtfwo34892vnm3,9rfx12j304y81-34m8905-");

            m_sRes = CxMacros::sAsTString(cszBuff);
            xTEST_EQ(std::tstring_t(cszBuff), m_sRes);
        }

        //8
        {
            const tchar_t cszBuff[] = {0};

            m_sRes = CxMacros::sAsTString(cszBuff);
            xTEST_EQ(std::tstring_t(cszBuff), m_sRes);
        }
    }

    //-------------------------------------
    //qualifiers
    xTEST_CASE(cullBlockLoops)
    {
        //xPR_SIZET
        {
            const size_t cuiValue = 2356567;

            m_sRes = CxString::sFormat(xT("%")xPR_SIZET, cuiValue);
            xTEST_EQ(CxString::lexical_cast(cuiValue), m_sRes);
        }

        //xPR_I64d
        {
            const longlong_t cllValue = 36745723;

            m_sRes = CxString::sFormat(xT("%")xPR_I64d, cllValue);
            xTEST_EQ(CxString::lexical_cast(cllValue), m_sRes);
        }

        //xPR_I64u
        {
            const ulonglong_t cullValue = 4767834;

            m_sRes = CxString::sFormat(xT("%")xPR_I64u, cullValue);
            xTEST_EQ(CxString::lexical_cast(cullValue), m_sRes);
        }

        //xPR_I64x
        {
            const longlong_t cllValue = 57830;

            m_sRes = CxString::sFormat(xT("%")xPR_I64x, cllValue);
            xTEST_EQ(CxString::sToLowerCase( CxString::lexical_cast(cllValue, 16) ), m_sRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
