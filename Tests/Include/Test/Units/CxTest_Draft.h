/**
 * \file   CxTest_Draft.h
 * \brief  draft for tests
 */


#ifndef CxTest_DraftH
#define CxTest_DraftH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTest_Draft :
    public CxTest
{
	public:
		              CxTest_Draft();
            ///< constructor
	    virtual      ~CxTest_Draft();
	        ///< destructor

	    virtual BOOL  bUnit       (const ULONGLONG cullBlockLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_DraftH
