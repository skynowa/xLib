/**
 * \file   CxTest_CxBackuper.h
 * \brief  test CxBackuper
 */


#ifndef CxTest_CxBackuperH
#define CxTest_CxBackuperH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxBackuper.h>
//---------------------------------------------------------------------------
class CxTest_CxBackuper :
    public CxTest
{
	public:
		              CxTest_CxBackuper();
            ///< constructor
	    virtual      ~CxTest_CxBackuper();
	        ///< destructor

	    virtual BOOL  bUnit(const ULONGLONG cullBlockLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxBackuperH
