/**
 * \file   CxTest_xDefines.cpp
 * \brief  test xDefines
 */


#include <Test/Common/CxTest_xDefines.h>

#include <xLib/Common/CxString.h>


//---------------------------------------------------------------------------
CxTest_xDefines::CxTest_xDefines() {

}
//---------------------------------------------------------------------------
CxTest_xDefines::~CxTest_xDefines() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_xDefines::bUnit(
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
    // qualifiers
    xTEST_CASE(cullCaseLoops)
    {
        // xPR_SIZET
        {
            const size_t cuiValue = 2356567;

            m_sRv = CxString::sFormat(xT("%")xPR_SIZET, cuiValue);
            xTEST_EQ(CxString::string_cast(cuiValue), m_sRv);
        }

        // xPR_I64d
        {
            const longlong_t cllValue = 36745723;

            m_sRv = CxString::sFormat(xT("%")xPR_I64d, cllValue);
            xTEST_EQ(CxString::string_cast(cllValue), m_sRv);
        }

        // xPR_I64u
        {
            const ulonglong_t cullValue = 4767834;

            m_sRv = CxString::sFormat(xT("%")xPR_I64u, cullValue);
            xTEST_EQ(CxString::string_cast(cullValue), m_sRv);
        }

        // xPR_I64x
        {
            const longlong_t cllValue = 57830;

            m_sRv = CxString::sFormat(xT("%")xPR_I64x, cllValue);
            xTEST_EQ(CxString::sToLowerCase( CxString::string_cast(cllValue, 16) ), m_sRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
