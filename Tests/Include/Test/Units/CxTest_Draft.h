/**
 * \file   CxTest_Draft.h
 * \brief  draft for tests
 */


#ifndef CxTest_DraftH
#define CxTest_DraftH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_Draft :
    public CxTest
{
    public:
                      CxTest_Draft();
            ///< constructor
        virtual      ~CxTest_Draft();
            ///< destructor

        virtual bool  bUnit       (const ulonglong_t cullCaseLoops);
            ///< unit test

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_DraftH
