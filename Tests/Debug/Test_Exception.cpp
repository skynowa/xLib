/**
 * \file   Test_Exception.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Exception)
xTEST_UNIT(Test_Exception)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Exception::unit()
{
    xTEST_CASE("Exception")
    {
        try {
            throw Exception();
        }
        catch (const Exception &e) {
            xTEST_EQ(Const::strEmpty(), e.what());
            //xTRACEV( xT("std::what: %s"), e.what().c_str() );
        }
        catch (...) {
            //xTRACE(xT("Exception unknown error"));
        }
    }

    xTEST_CASE("Exception(std::tstring_t)")
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("TEST_STRING_1")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3")},
            {xT("TEST_STRING_4"),        xT("TEST_STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            try {
                throw Exception() << sTestData[i][0].c_str() << xT(".");
            }
            catch (const Exception &e) {
                xTEST_EQ(sTestData[i][1] + xT("."), e.what());
                //xTRACEV( xT("std::what: %s"), e.what().c_str() );
            }
            catch (...) {
                //xTRACE(xT("std::exception unknown error"));
            }
        }
    }

    xTEST_CASE("catch Exception")
    {
        try {
            throw Exception() << xT("Exception_test_exception");
        }
        catch (const Exception &e) {
            //xTRACEV( xT("std::what: %s"), e.what().c_str() );
        }
        catch (...) {
            //xTRACE(xT("std::exception unknown error"));
        }
    }

    xTEST_CASE("catch std::exception")
    {
        try {
            std::tstring_t sStr;

            sStr.at(0);
        }
        catch (const std::exception &e) {
            //xTRACEV( xT("std::what: %s"), e.what() );
        }
        catch (...) {
            //xTRACE(xT("std::exception unknown error"));
        }
    }

    xTEST_CASE("xTRY, xTHROW, xCATCH_ALL")
    {
        #if 0
            xTRY {
                /*
                std::tstring_t sStr;

                sStr.at(0);
                */

                xTHROW() << xT("Function: ") << xFUNCTION << xT(" Line: ") << xLINE;
            }
            xCATCH_ALL;

            xTRY {
                std::tstring_t sStr;

                sStr.at(0);
            }
            xCATCH_ALL;
        #endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
