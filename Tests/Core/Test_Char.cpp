/**
 * \file   Test_Char.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Char)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Char::unit()
{
    xTEST_CASE("isAlphaNum")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("sefasdf3456SDRFGW2345f235vdfs3e45v234624uhethQWER23141scvf");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isAlphaNum();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*&*(&*()*)+_=-) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isAlphaNum();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isAlpha")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isAlpha();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*1234567890-=&*(&*()*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isAlpha();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isControl")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isControl();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wert12345wecrtwe67WERTWE890-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isControl();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isDigitDec")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isDigitDec();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wertwecrtweWERTWE-=&*(&*(wetf)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isDigitDec();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isDigitHex")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("0123456789abcdefABCDEF");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isDigitHex();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" !@$#%^%*wrtwrtwWRTW-=&*(&*(wt)*)+_) /*-+{}?><< :\"||");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isDigitHex();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isGraph")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isGraph();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f ");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isGraph();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isPrint")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" 1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isPrint();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isPrint();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isPunct")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isPunct();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT(" qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz\t\n\a\t\r\n\v\b\f");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isPunct();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isSpace")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT(" \t\n\v\f\r");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isSpace();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("qwcrqwerWETYRBTY125235645656fgderKUIOPMTYjcxz!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isSpace();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isLower")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("abcdefghijklmnopqrstuvwxyz");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isLower();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("WETYRBTY125235645656FGDERKUIOPMTY!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isLower();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("isUpper")
    {
        // true
        {
            std::ctstring_t dataTrue  = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

            for (size_t i = 0; i < dataTrue.size(); ++ i) {
                m_bRv = CharT(dataTrue.at(i)).isUpper();
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::ctstring_t dataFalse = xT("wetyrbty125235645656fgderkuiopmty!@#$%^&*()_+*-+/{}|:;><?");

            for (size_t i = 0; i < dataFalse.size(); ++ i) {
                m_bRv = CharT(dataFalse.at(i)).isUpper();
                xTEST(!m_bRv);
            }
        }
    }

    xTEST_CASE("toLower")
    {
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");

        for (size_t i = 0; i < dataUpper.size(); ++ i) {
            m_chRv = CharT(dataUpper.at(i)).toLower().get();
            xTEST_EQ(m_chRv, dataLow.at(i));
        }
    }

    xTEST_CASE("toUpper")
    {
        std::ctstring_t dataLow   = xT("abcdefghijklmnopqrstuvwxyz");
        std::ctstring_t dataUpper = xT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

        for (size_t i = 0; i < dataLow.size(); ++ i) {
            m_chRv = CharT(dataLow.at(i)).toUpper().get();
            xTEST_EQ(m_chRv, dataUpper.at(i));
        }
    }

    xTEST_CASE("symbol")
    {
        using data_t = Data2<tchar_t, std::tstring_t>;

        const std::vector<data_t> data
        {
            {xT('a'),  xT("a")},
            {xT('b'),  xT("b")},
            {xT('0'),  xT("0")},
            {xT('1'),  xT("1")},
            {xT('?'),  xT("?")},
            {xT('\0'), xT("<NUL>")},
            {0,        xT("<NUL>")},
            {31,       xT("<US>")},
            {32,       std::tstring_t(1, 32)},
            {126,      std::tstring_t(1, 126)},
            {127,      xT("<?>")},
            {255,      xT("<?>")}
        };

        for (const auto &it_data : data) {
            m_sRv = CharT(it_data.test).symbol();
            xTEST_EQ(m_sRv, it_data.expect);
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
