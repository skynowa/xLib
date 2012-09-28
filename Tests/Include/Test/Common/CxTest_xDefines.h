/**
 * \file   CxTest_xDefines.h
 * \brief  test xDefines
 */


#ifndef CxTest_xDefinesH
#define CxTest_xDefinesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Common/xDefines.h>
//---------------------------------------------------------------------------
class CxTest_xDefines :
    public CxTest
{
    public:
                      CxTest_xDefines();
            ///< constructor
        virtual      ~CxTest_xDefines();
            ///< destructor

        virtual bool  bUnit(const ulonglong_t cullCaseLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_xDefinesH
