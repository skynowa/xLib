/**
 * \file   CxTest_xDefines.cpp
 * \brief  test xDefines
 */


#include <Test/Common/CxTest_xDefines.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>


//------------------------------------------------------------------------------
CxTest_xDefines::CxTest_xDefines() {

}
//------------------------------------------------------------------------------
CxTest_xDefines::~CxTest_xDefines() {

}
//------------------------------------------------------------------------------
/*virtual*/
void_t
CxTest_xDefines::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("xDefines::combinations of preprocessor defines", a_cullCaseLoops)
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

    xTEST_CASE("xDefines::xLEX_TO_STR_", a_cullCaseLoops)
    {
        long_t liVal = - 1;

        m_sRv = xLEX_TO_STR(liVal);
        xTEST_EQ(std::tstring_t(xT("liVal")), m_sRv);

        xUNUSED(liVal);
    }

    xTEST_CASE("xDefines::xLEX_CAT_", a_cullCaseLoops)
    {
        std::tstring_t sVal;

        xLEX_CAT(s, Val) = xT("XLIB_VAL");
        xTEST_EQ(std::tstring_t(xT("XLIB_VAL")), sVal);

        sVal.clear();
    }

    xTEST_CASE("xDefines::xTEXT_ xT_", a_cullCaseLoops)
    {
        std::ctstring_t csStr(xT("xxx"));

        m_sRv = xTEXT("xxx");
        xTEST_EQ(csStr, m_sRv);

        m_sRv = xT("xxx");
        xTEST_EQ(csStr, m_sRv);
    }

    xTEST_CASE("xDefines::xS2US_", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::xUS2S_", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::xS2TS_", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::xTS2S_", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::utils", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::xUNUSED", a_cullCaseLoops)
    {
        size_t uiArg = 0U;

        xUNUSED(uiArg);
    }

    xTEST_CASE("xDefines::temporary enable disable code", a_cullCaseLoops)
    {
        xTEST_EQ(1, xTEMP_ENABLED);
        xTEST_EQ(0, xTEMP_DISABLED);
        xTEST_EQ(0, xDEPRECIATE);
        xTEST_EQ(0, xTODO);
        xTEST_EQ(0, xCAN_REMOVE);
        xTEST_EQ(0, xNOT_COMPILE);
        xTEST_EQ(0, xTEST_IGNORE);
        xTEST_EQ(1, xREVIEW);
        xTEST_EQ(0, xCOMMENT);

        xTEST_NA(var);
        xTESTS_NA;
        xNA;
    }

    xTEST_CASE("xDefines::buildin macroses", a_cullCaseLoops)
    {

    }

    xTEST_CASE("xDefines::xFILE_", a_cullCaseLoops)
    {
        m_sRv = xFILE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xLINE_", a_cullCaseLoops)
    {
        m_ulRv = xLINE;
        xTEST_GR(0UL, m_ulRv);
    }

    xTEST_CASE("xDefines::xFUNCTION_", a_cullCaseLoops)
    {
        m_sRv = xFUNCTION;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xDATE_", a_cullCaseLoops)
    {
        m_sRv = xDATE;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xTIME_", a_cullCaseLoops)
    {
        m_sRv = xTIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xDATETIME_", a_cullCaseLoops)
    {
        m_sRv = xDATETIME;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xCOUNTER_", a_cullCaseLoops)
    {
        m_sRv = CxString::cast(xCOUNTER);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::function params", a_cullCaseLoops)
    {
        struct STest {
            std::tstring_t execute(
                xIN     cint_t       &a_iVal,
                xOUT    std::csize_t &a_uiVal,
                xIN_OUT tchar_t      *a_piVal)
            {
                std::tstringstream_t sstStream;

                sstStream << xT("a_iVal=")  << a_iVal
                          << xT("a_uiVal=") << a_uiVal
                          << xT("a_piVal=") << a_piVal;

                return sstStream.str();
            }
        };

        STest   tsTest;
        tchar_t szBuff[10 + 1] = {0};

        m_sRv = tsTest.execute(10, 15U, szBuff);
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xHOST_NAME_MAX_", a_cullCaseLoops)
    {
        m_iRv = xHOST_NAME_MAX;
        xTEST_GR(0, m_iRv);
    }

    xTEST_CASE("xDefines::xPATH_MAX_", a_cullCaseLoops)
    {
        m_stRv = xPATH_MAX;
        xTEST_GR(m_stRv, size_t(0U));
    }

    xTEST_CASE("xDefines::xNAME_MAX_", a_cullCaseLoops)
    {
        m_stRv = xNAME_MAX;
        xTEST_GR(m_stRv, size_t(0U));
    }

    xTEST_CASE("xDefines::xLINE_MAX_", a_cullCaseLoops)
    {
        m_stRv = xLINE_MAX;
        xTEST_GR(m_stRv, size_t(0U));
    }

    xTEST_CASE("xDefines::xENV_MAX_", a_cullCaseLoops)
    {
        m_stRv = xENV_MAX;
        xTEST_GR(m_stRv, size_t(0U));
    }

    xTEST_CASE("xDefines::xFRAMES_MAX_", a_cullCaseLoops)
    {
        m_ulRv = xSTACK_TRACE_FRAMES_MAX;
        xTEST_GR(m_ulRv, 0UL);
    }

    xTEST_CASE("xDefines::xSEMAPHORE_VALUE_MAX_", a_cullCaseLoops)
    {
        m_liRv = xSEMAPHORE_VALUE_MAX;
        xTEST_GR(m_liRv, 0L);
    }

    xTEST_CASE("xDefines::var args", a_cullCaseLoops)
    {
        std::ctstring_t csVal = xT("aaa");
        cint_t            ciVal = 100;

        // CxString::format use var args
        m_sRv = CxString::format(xT("%s, %d"), csVal.c_str(), ciVal);
        xTEST_EQ(std::tstring_t(xT("aaa, 100")), m_sRv);
    }

    xTEST_CASE("xDefines::qualifiers", a_cullCaseLoops)
    {
        // xPR_SIZET
        {
            std::csize_t cuiValue = 2356567U;

            m_sRv = CxString::format(xT("%")xPR_SIZET, cuiValue);
            xTEST_EQ(CxString::cast(cuiValue), m_sRv);
        }

        // xPR_I64d
        {
            clonglong_t cllValue = 36745723LL;

            m_sRv = CxString::format(xT("%")xPR_I64d, cllValue);
            xTEST_EQ(CxString::cast(cllValue), m_sRv);
        }

        // xPR_I64u
        {
            culonglong_t cullValue = 4767834ULL;

            m_sRv = CxString::format(xT("%")xPR_I64u, cullValue);
            xTEST_EQ(CxString::cast(cullValue), m_sRv);
        }

        // xPR_I64x
        {
            clonglong_t cllValue = 57830LL;

            m_sRv = CxString::format(xT("%")xPR_I64x, cllValue);
            xTEST_EQ(CxString::toLowerCase( CxString::cast(cllValue, 16) ), m_sRv);
        }
    }


    xTEST_CASE("xDefines::xTIMEOUT_INFINITE_", a_cullCaseLoops)
    {
        m_ullRv = xTIMEOUT_INFINITE;
    }

    xTEST_CASE("xDefines::xPAGE_SIZE_", a_cullCaseLoops)
    {
        #if xOS_ENV_UNIX
            m_stRv = xPAGE_SIZE;
            xTEST_GR(m_stRv, size_t(0U));
        #endif
    }

    xTEST_CASE("xDefines::xDIR_TEMP_ temprory directory", a_cullCaseLoops)
    {
        m_sRv = xDIR_TEMP;
        xTEST_EQ(false, m_sRv.empty());
    }

    xTEST_CASE("xDefines::xNATIVE_HANDLE_NULL_ xNATIVE_HANDLE_INVALID_", a_cullCaseLoops)
    {
       native_handle_t nhNull    = xNATIVE_HANDLE_NULL;
       xUNUSED(nhNull);

       native_handle_t nhInvalid = xNATIVE_HANDLE_INVALID;
       xUNUSED(nhInvalid);
    }

    xTEST_CASE("xDefines::xFOREACH_", a_cullCaseLoops)
    {
        // xFOREACH
        {
            std::ctstring_t csNew = xT("xxxxxx");

            std::vec_tstring_t vsData;
            vsData.push_back(xT("aaaaaa"));
            vsData.push_back(xT("bbbbbb"));
            vsData.push_back(xT("cccccc"));

            xFOREACH(std::vec_tstring_t, it, vsData) {
                *it = csNew;
            }

            xFOREACH(std::vec_tstring_t, it, vsData) {
                xTEST_EQ(*it, csNew);
            }
        }

        // xFOREACH_CONST
        {
            std::ctstring_t csNew = xT("xxxxxx");
            std::vec_tstring_t   vsDataNew;

            std::vec_tstring_t   vsData;
            vsData.push_back(csNew);
            vsData.push_back(csNew);
            vsData.push_back(csNew);

            xFOREACH_CONST(std::vec_tstring_t, it, vsData) {
                vsDataNew.push_back(*it);
            }

            xFOREACH(std::vec_tstring_t, it, vsDataNew) {
                xTEST_EQ(*it, csNew);
            }
        }

        // xFOREACH_R
        {
            std::ctstring_t csNew = xT("xxxxxx");

            std::vec_tstring_t vsData;
            vsData.push_back(xT("aaaaaa"));
            vsData.push_back(xT("bbbbbb"));
            vsData.push_back(xT("cccccc"));

            xFOREACH_R(std::vec_tstring_t, it, vsData) {
                *it = csNew;
            }

            xFOREACH_R(std::vec_tstring_t, it, vsData) {
                xTEST_EQ(*it, csNew);
            }
        }

        // xFOREACH_R_CONST
        {
            std::ctstring_t csNew = xT("xxxxxx");
            std::vec_tstring_t   vsDataNew;

            std::vec_tstring_t   vsData;
            vsData.push_back(csNew);
            vsData.push_back(csNew);
            vsData.push_back(csNew);

            xFOREACH_R_CONST(std::vec_tstring_t, it, vsData) {
                vsDataNew.push_back(*it);
            }

            xFOREACH_R_CONST(std::vec_tstring_t, it, vsDataNew) {
                xTEST_EQ(*it, csNew);
            }
        }
    }

    //--------------------------------------------------
    // etc
    xTEST_CASE("xDefines::etc", a_cullCaseLoops)
    {

    }
}
//------------------------------------------------------------------------------
