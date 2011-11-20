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
/*virtual*/
bool
CxTest_CxChar::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bIsAlphaNum
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsAlpha
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsControl
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitDec
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("0123456789");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitHex
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsGraph
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsPrint
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataFalse.at(i));
                #if xTODO
                    xTEST_EQ(false, m_bRes);
                #endif
            }
        }
    }

    //--------------------------------------------------
    //bIsPunct
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsSpace
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsLower
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsUpper
    xTEST_BLOCK(cullBlockLoops)
    {
        //true
        {
            const std::tstring sDataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataTrue.at(i));
                xTEST_DIFF(false, m_bRes);
            }
        }

        //false
        {
            const std::tstring sDataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataFalse.at(i));
                xTEST_EQ(false, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //chToLower
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        const std::tstring sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < sDataUpper.size(); ++ i) {
            m_chRes = CxChar::chToLower(sDataUpper.at(i));
            xTEST_EQ(sDataLow.at(i), m_chRes);
        }
    }

    //--------------------------------------------------
    //chToUpper
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::tstring sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        const std::tstring sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < sDataLow.size(); ++ i) {
            m_chRes = CxChar::chToUpper(sDataLow.at(i));
            xTEST_EQ(sDataUpper.at(i), m_chRes);
        }
    }

    return true;
}
//---------------------------------------------------------------------------
