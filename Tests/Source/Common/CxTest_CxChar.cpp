/****************************************************************************
* Class name:  CxTest_CxChar
* Description: test CxChar
* File name:   CxTest_CxChar.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxChar (constructor)
CxTest_CxChar::CxTest_CxChar() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxChar (destructor)
CxTest_CxChar::~CxTest_CxChar() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxChar::bUnit() {
    //--------------------------------------------------
    //bIsAlphaNum
    {
        //TRUE
        {
            const tString sDataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf@#$");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlphaNum(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsAlpha
    {
        //TRUE
        {
            const tString sDataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsAlpha(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsControl
    {
        //TRUE
        {
            const tString sDataTrue  = xT("\t\n\a\t\r\n\v\b\f\?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsControl(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitDec
    {
        //TRUE
        {
            const tString sDataTrue  = xT("0123456789");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitDec(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsDigitHex
    {
        //TRUE
        {
            const tString sDataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsDigitHex(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsGraph
    {
        //TRUE
        {
            const tString sDataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT("\t\n\a\t\r\n\v\b\f\? ");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsGraph(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsPrint
    {
        //TRUE
        {
            const tString sDataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT("\t\n\a\t\r\n\v\b\f\?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPrint(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsPunct
    {
        //TRUE
        {
            const tString sDataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f\?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsPunct(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsSpace
    {
        //TRUE
        {
            const tString sDataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsSpace(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsLower
    {
        //TRUE
        {
            const tString sDataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsLower(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bIsUpper
    {
        //TRUE
        {
            const tString sDataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataTrue.at(0));
                xASSERT(FALSE != m_bRes);
            }
        }

        //FALSE
        {
            const tString sDataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRes = CxChar::bIsUpper(sDataFalse.at(0));
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //chToLower
    {
        const tString sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        const tString sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < sDataUpper.size(); ++ i) {
            m_chRes = CxChar::chToLower(sDataUpper.at(0));
            xASSERT(sDataLow.at(0) == m_chRes);
        }
    }

    //--------------------------------------------------
    //chToUpper
    {
        const tString sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        const tString sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < sDataLow.size(); ++ i) {
            m_chRes = CxChar::chToUpper(sDataLow.at(0));
            xASSERT(sDataUpper.at(0) == m_chRes);
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
