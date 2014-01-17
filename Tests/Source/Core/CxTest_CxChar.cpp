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
        // true
        {
            std::ctstring_t dataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isAlphaNum();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isAlphaNum();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isAlpha", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isAlpha();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isAlpha();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isControl", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isControl();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isControl();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isDigitDec", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isDigitDec();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isDigitDec();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isDigitHex", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isDigitHex();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isDigitHex();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isGraph", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isGraph();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isGraph();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isPrint", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isPrint();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isPrint();
                // TEST: CxChar(xxxx).isPrint
                // xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isPunct", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isPunct();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isPunct();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isSpace", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isSpace();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isSpace();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isLower", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isLower();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isLower();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::isUpper", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CxChar(dataTrue.at(i)).isUpper();
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CxChar(dataFalse.at(i)).isUpper();
                xTEST_EQ(false, m_bRv);
            }
        }
    }

    xTEST_CASE("CxChar::toLower", a_caseLoops)
    {
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < dataUpper.size(); ++ i) {
            m_chRv = CxChar(dataUpper.at(i)).toLower();
            xTEST_EQ(dataLow.at(i), m_chRv);
        }
    }

    xTEST_CASE("CxChar::toUpper", a_caseLoops)
    {
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < dataLow.size(); ++ i) {
            m_chRv = CxChar(dataLow.at(i)).toUpper();
            xTEST_EQ(dataUpper.at(i), m_chRv);
        }
    }
}
//------------------------------------------------------------------------------
