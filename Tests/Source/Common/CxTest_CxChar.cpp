/****************************************************************************
* Class name:  CxTest_CxChar
* Description: test CxChar
* File name:   CxTest_CxChar.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxChar.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxChar
CxTest_CxChar::CxTest_CxChar() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxChar
CxTest_CxChar::~CxTest_CxChar() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxChar::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //bIsAlphaNum
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsAlpha
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsControl
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitDec
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("0123456789");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitHex
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsGraph
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsPrint
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataFalse.at(i));
                #if xTODO
                    xASSERT_EQ(FALSE, m_bRes);
                #endif
            }
        }
    }

    //--------------------------------------------------
    //bIsPunct
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsSpace
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsLower
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsUpper
    xTEST_BLOCK(cullBlockLoops)
    {
        //TRUE
        {
            const std::tstring sDataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataTrue.at(i));
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //FALSE
        {
            const std::tstring sDataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataFalse.at(i));
                xASSERT_EQ(FALSE, m_bRes);
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
            xASSERT_EQ(sDataLow.at(i), m_chRes);
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
            xASSERT_EQ(sDataUpper.at(i), m_chRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
