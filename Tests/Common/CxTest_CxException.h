/****************************************************************************
* Class name:  CxTest_CxException
* Description: test CxException
* File name:   CxTest_CxException.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxExceptionH
#define CxTest_CxExceptionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxException.h>
//---------------------------------------------------------------------------
class CxTest_CxException :
    public CxTest
{
    public:
        CxTest_CxException();
        virtual     ~CxTest_CxException();

        /*virtual*/ BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxException (constructor)
CxTest_CxException::CxTest_CxException() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxException (destructor)
CxTest_CxException::~CxTest_CxException() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxException::bUnit() {
    //--------------------------------------------------
    //CxException(), sGetWhat, e.sGetName
    {
        try {
            throw CxException();
        }
        catch (CxException &e) {
            xASSERT(tString() == e.sGetWhat());
            //xTRACEV( xT("sGetName: %s, sGetWhat: %s"), e.sGetName().c_str(), e.sGetWhat().c_str() );
        }
        catch (...) {
            xTRACE(xT("CxException unknown error"));
        }
    }

    //--------------------------------------------------
    //CxException(tString), what
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
                xASSERT( sTestData[i][1] == e.sGetWhat() );
                //xTRACEV( xT("sGetName: %s, sGetWhat: %s"), e.sGetName().c_str(), e.sGetWhat().c_str() );
            }
            catch (...) {
                xTRACE(xT("CxException unknown error"));
            }
        }
    }

    //--------------------------------------------------
    //CxException(), sGetWhat, e.sGetName
    {
        try {
            //tString sStr; sStr.at(0);
            //throw CxException() << "xxxxxx";
        }

    #if xTEMP_DISABLED
        catch (std::exception &e) {
            xASSERT(tString() == e.sGetWhat());
            xTRACEV( xT("sGetName: %s, sGetWhat: %s"), e.sGetName().c_str(), e.sGetWhat().c_str() );
        }
    #endif

        catch (CxException &e) {
            xTRACEV( xT("sGetWhat: %s, sGetClassName: %s"), e.sGetWhat().c_str(), e.sGetClassName().c_str() );
        }

    #if 1
        catch (std::exception &e) {
            xTRACEV( xT("std::what: %s"), e.what() );
        }
    #endif

    #if xTEMP_DISABLED
        catch (CxException &e) {
            xTRACEV( xT("sGetWhat: %s, sGetClassName: %s"), e.sGetWhat().c_str(), e.sGetClassName().c_str() );
        }
    #endif

        catch (...) {
            xTRACE(xT("CxException unknown error"));
        }
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxExceptionH
