/**
 * \file   CxTest_CxChar.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxChar.h>


//---------------------------------------------------------------------------
CxTest_CxChar::CxTest_CxChar() {

}
//---------------------------------------------------------------------------
CxTest_CxChar::~CxTest_CxChar() {

}
//---------------------------------------------------------------------------
/* virtual */
bool
CxTest_CxChar::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bIsAlphaNum
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsAlphaNum(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsAlphaNum(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsAlpha
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsAlpha(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsAlpha(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsControl
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsControl(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsControl(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitDec
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("0123456789");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsDigitDec(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsDigitDec(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitHex
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsDigitHex(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsDigitHex(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsGraph
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsGraph(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsGraph(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsPrint
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsPrint(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsPrint(sDataFalse.at(i));
                #if xTODO
                    xTEST_EQ(false, m_bRv);
                #endif
            }
        }
    }

    //--------------------------------------------------
    //bIsPunct
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsPunct(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsPunct(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsSpace
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsSpace(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsSpace(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsLower
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsLower(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsLower(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //bIsUpper
    xTEST_CASE(cullCaseLoops)
    {
        //true
        {
            const std::tstring_t sDataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::bIsUpper(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            const std::tstring_t sDataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::bIsUpper(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    //--------------------------------------------------
    //chToLower
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        const std::tstring_t sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < sDataUpper.size(); ++ i) {
            m_chRv = CxChar::chToLower(sDataUpper.at(i));
            xTEST_EQ(sDataLow.at(i), m_chRv);
        }
    }

    //--------------------------------------------------
    //chToUpper
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        const std::tstring_t sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < sDataLow.size(); ++ i) {
            m_chRv = CxChar::chToUpper(sDataLow.at(i));
            xTEST_EQ(sDataUpper.at(i), m_chRv);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
