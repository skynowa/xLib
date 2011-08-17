/****************************************************************************
* Class name:  CxTest_CxException
* Description: test CxException
* File name:   CxTest_CxException.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Common/CxTest_CxException.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxException
CxTest_CxException::CxTest_CxException() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxException
CxTest_CxException::~CxTest_CxException() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxException::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    //--------------------------------------------------
    //CxException(), sGetWhat, e.sGetName
    xTEST_BLOCK(cullBlockLoops)
    {
        try {
            throw CxException();
        }
        catch (CxException &e) {
            xASSERT_EQ(tString(), e.sGetWhat());
            //xTRACEV( xT("std::what: %s"), e.sGetWhat().c_str() );
        }
        catch (...) {
            //xTRACE(xT("CxException unknown error"));
        }
    }

    //--------------------------------------------------
    //CxException(tString), what
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString sTestData[][2] = {
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
                xASSERT_EQ(sTestData[i][1], e.sGetWhat());
                //xTRACEV( xT("std::what: %s"), e.sGetWhat().c_str() );
            }
            catch (...) {
                //xTRACE(xT("std::exception unknown error"));
            }
        }
    }

    //--------------------------------------------------
    //catch CxException
    xTEST_BLOCK(cullBlockLoops)
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
    xTEST_BLOCK(cullBlockLoops)
    {
        try {
            tString sStr;

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
    xTEST_BLOCK(cullBlockLoops) {
        #if xTODO
            xTRY {
                tString sStr;

                sStr.at(0);
            }
            xCATCH_ALL;

            return TRUE;
        #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
