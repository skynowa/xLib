/**
 * \file   CxTest_CxSystemLog.h
 * \brief  test CxSystemLogs
 */


#ifndef CxTest_CxSystemLogH
#define CxTest_CxSystemLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Log/CxSystemLog.h>
//---------------------------------------------------------------------------
class CxTest_CxSystemLog:
    public CxTest
{
	public:
		              CxTest_CxSystemLog();
            ///< constructor
	    virtual      ~CxTest_CxSystemLog();
	        ///< destructor

	    virtual bool  bUnit(const ulonglong_t cullBlockLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxSystemLogH
