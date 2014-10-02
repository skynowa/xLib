/**
 * \file   Test_Char.cpp
 * \brief
 */


#include <Test/Core/Test_Char.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
Test_Char::unit(
    culonglong_t &a_caseLoops
)
{
    xTEST_CASE("Char::isAlphaNum", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isAlphaNum();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isAlphaNum();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isAlpha", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isAlpha();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isAlpha();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isControl", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isControl();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isControl();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isDigitDec", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isDigitDec();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isDigitDec();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isDigitHex", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isDigitHex();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isDigitHex();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isGraph", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isGraph();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isGraph();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isPrint", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isPrint();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isPrint();
                // TEST: Char::isPrint()
                // xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isPunct", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isPunct();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isPunct();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isSpace", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isSpace();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isSpace();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isLower", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isLower();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isLower();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::isUpper", a_caseLoops)
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = Char(dataTrue.at(i)).isUpper();
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = Char(dataFalse.at(i)).isUpper();
                xTEST_EQ(m_bRv, false);
            }
        }
    }

    xTEST_CASE("Char::toLower", a_caseLoops)
    {
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < dataUpper.size(); ++ i) {
            m_chRv = Char(dataUpper.at(i)).toLower();
            xTEST_EQ(dataLow.at(i), m_chRv);
        }
    }

    xTEST_CASE("Char::toUpper", a_caseLoops)
    {
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < dataLow.size(); ++ i) {
            m_chRv = Char(dataLow.at(i)).toUpper();
            xTEST_EQ(dataUpper.at(i), m_chRv);
        }
    }
}
//-------------------------------------------------------------------------------------------------
