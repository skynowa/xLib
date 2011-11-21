/**
 * \file   CxTest_CxCurrentProcess.h
 * \brief  test CxCurrentProcess
 */


#ifndef CxTest_CxCurrentProcessH
#define CxTest_CxCurrentProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxCurrentProcess.h>
//---------------------------------------------------------------------------
class CxTest_CxCurrentProcess :
    public CxTest
{
	public:
		              CxTest_CxCurrentProcess();
            ///< constructor
	    virtual      ~CxTest_CxCurrentProcess();
	        ///< destructor

	    virtual bool  bUnit(const ulonglong_t cullBlockLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCurrentProcessH
