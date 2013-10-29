/**
 * \file   CxTest_CxException.cpp
 * \brief
 */


#include <Test/Debug/CxTest_CxException.h>

#include <xLib/Core/CxConst.h>


//------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxException::unit(
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_CASE("CxException::CxException", a_cullCaseLoops)
    {
        try {
            throw CxException();
        }
        catch (const CxException &e) {
            xTEST_EQ(CxConst::xSTR_EMPTY(), e.what());
            //xTRACEV( xT("std::what: %s"), e.what().c_str() );
        }
        catch (...) {
            //xTRACE(xT("CxException unknown error"));
        }
    }

    xTEST_CASE("CxException::CxException(std::tstring_t)", a_cullCaseLoops)
    {
        std::ctstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("TEST_STRING_1")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3")},
            {xT("TEST_STRING_4"),        xT("TEST_STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            try {
                throw CxException() << sTestData[i][0].c_str() << xT(".");
            }
            catch (const CxException &e) {
                xTEST_EQ(sTestData[i][1] + xT("."), e.what());
                //xTRACEV( xT("std::what: %s"), e.what().c_str() );
            }
            catch (...) {
                //xTRACE(xT("std::exception unknown error"));
            }
        }
    }

    xTEST_CASE("CxException::[catch CxException]", a_cullCaseLoops)
    {
        try {
            throw CxException() << xT("CxException_test_exception");
        }
        catch (const CxException &e) {
            //xTRACEV( xT("std::what: %s"), e.what().c_str() );
        }
        catch (...) {
            //xTRACE(xT("std::exception unknown error"));
        }
    }

    xTEST_CASE("CxException::[catch std::exception]", a_cullCaseLoops)
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

    xTEST_CASE("CxException::xTRY_ xCATCH_ALL_ xTHROW_", a_cullCaseLoops)
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
}
//------------------------------------------------------------------------------
