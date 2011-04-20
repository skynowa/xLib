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
class CxTest_CxException : public CxTest {
    public:
        CxTest_CxException();
        virtual     ~CxTest_CxException();

        /*virtual*/ BOOL bUnit();

    private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxException (constructor)
CxTest_CxException::CxTest_CxException() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxException (destructor)
CxTest_CxException::~CxTest_CxException() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxException::bUnit() {
    //--------------------------------------------------
    //CxException(), what
    //{
    //    try {
    //        throw CxException();
    //    } catch (CxException &e) {
    //        xASSERT(std::string() == e.what());
    //        ////xSTD_COUT(e.what());
    //    }
    //}

    //--------------------------------------------------
    //CxException(tString), what
    //{
    //    const tString sTestData[][2] = {
    //        {xT("TEST_STRING_1"),        xT("TEST_STRING_1")},
    //        {xT("TEST_STRING_2"),        xT("TEST_STRING_2")},
    //        {xT("TEST_STRING_3"),        xT("TEST_STRING_3")},
    //        {xT("TEST_STRING_4"),        xT("TEST_STRING_4")}
    //    };

    //    for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
    //        try {
    //            throw CxException() << sTestData[i][0].c_str();
    //        } catch (CxException &e) {
    //            std::string sRes = e.what();

    //            xASSERT( sTestData[i][1] == tString(sRes.begin(), sRes.end()) );
    //            ////xSTD_COUT(e.what());
    //        }
    //    }
    //}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxExceptionH

