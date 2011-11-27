/**
 * \file   CxTest_CxException.cpp
 * \brief
 */


#include <Test/Common/CxTest_CxException.h>


//---------------------------------------------------------------------------
CxTest_CxException::CxTest_CxException() {

}
//---------------------------------------------------------------------------
CxTest_CxException::~CxTest_CxException() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxException::bUnit(
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //CxException(), sGetWhat, e.sGetName
    xTEST_CASE(cullCaseLoops)
    {
        try {
            throw CxException();
        }
        catch (CxException &e) {
            xTEST_EQ(CxConst::xSTR_EMPTY, e.sGetWhat());
            //xTRACEV( xT("std::what: %s"), e.sGetWhat().c_str() );
        }
        catch (...) {
            //xTRACE(xT("CxException unknown error"));
        }
    }

    //--------------------------------------------------
    //CxException(std::tstring_t), what
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t sTestData[][2] = {
            {xT("TEST_STRING_1"),        xT("TEST_STRING_1")},
            {xT("TEST_STRING_2"),        xT("TEST_STRING_2")},
            {xT("TEST_STRING_3"),        xT("TEST_STRING_3")},
            {xT("TEST_STRING_4"),        xT("TEST_STRING_4")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            try {
                throw CxException() << sTestData[i][0].c_str();
            }
            catch (CxException &e) {
                xTEST_EQ(sTestData[i][1], e.sGetWhat());
                //xTRACEV( xT("std::what: %s"), e.sGetWhat().c_str() );
            }
            catch (...) {
                //xTRACE(xT("std::exception unknown error"));
            }
        }
    }

    //--------------------------------------------------
    //catch CxException
    xTEST_CASE(cullCaseLoops)
    {
        try {
            throw CxException() << "CxException_test_exception";
        }
        catch (CxException &e) {
            //xTRACEV( xT("std::what: %s"), e.sGetWhat().c_str() );
        }
        catch (...) {
            //xTRACE(xT("std::exception unknown error"));
        }
    }

    //--------------------------------------------------
    //catch std::exception
    xTEST_CASE(cullCaseLoops)
    {
        try {
            std::tstring_t sStr;

            sStr.at(0);
        }
        catch (std::exception &e) {
            //xTRACEV( xT("std::what: %s"), e.what() );
        }
        catch (...) {
            //xTRACE(xT("std::exception unknown error"));
        }
    }

    //--------------------------------------------------
    //
    xTEST_CASE(cullCaseLoops) {
        #if xTODO
            xTRY {
                std::tstring_t sStr;

                sStr.at(0);
            }
            xCATCH_ALL;

            return true;
        #endif
    }

    return true;
}
//---------------------------------------------------------------------------
