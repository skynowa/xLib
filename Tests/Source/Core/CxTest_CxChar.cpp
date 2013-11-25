/**
 * \file   CxTest_CxChar.cpp
 * \brief
 */


#include <Test/Core/CxTest_CxChar.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxChar::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("CxChar::isAlphaNum", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isAlphaNum(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isAlphaNum(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isAlpha", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isAlpha(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isAlpha(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isControl", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isControl(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isControl(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isDigitDec", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("0123456789");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isDigitDec(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isDigitDec(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isDigitHex", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isDigitHex(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isDigitHex(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isGraph", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isGraph(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isGraph(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isPrint", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isPrint(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isPrint(sDataFalse.at(i));
                // TEST: CxChar::isPrint
                // xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isPunct", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isPunct(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isPunct(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isSpace", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isSpace(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isSpace(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isLower", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isLower(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isLower(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isUpper", a_caseLoops)
    {
        //true
        {
            std::ctstring_t sDataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < sDataTrue.size(); ++ i) {
                m_bRv = CxChar::isUpper(sDataTrue.at(i));
                xTEST_EQ(true, m_bRv);
            }
        }

        //false
        {
            std::ctstring_t sDataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < sDataFalse.size(); ++ i) {
                m_bRv = CxChar::isUpper(sDataFalse.at(i));
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::toLower", a_caseLoops)
    {
        std::ctstring_t sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        std::ctstring_t sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < sDataUpper.size(); ++ i) {
            m_chRv = CxChar::toLower(sDataUpper.at(i));
            xTEST_EQ(sDataLow.at(i), m_chRv);
        }
    }

    xTEST_CASE("CxChar::toUpper", a_caseLoops)
    {
        std::ctstring_t sDataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        std::ctstring_t sDataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < sDataLow.size(); ++ i) {
            m_chRv = CxChar::toUpper(sDataLow.at(i));
            xTEST_EQ(sDataUpper.at(i), m_chRv);
        }
    }
}
//------------------------------------------------------------------------------
