/**
 * \file   CxTest_CxProcessInfo.h
 * \brief  test CxProcessInfo
 */


#ifndef CxTest_Common_CxProcessInfoH
#define CxTest_Common_CxProcessInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Common/CxProcessInfo.h>
//---------------------------------------------------------------------------
class CxTest_CxProcessInfo :
    public CxTest
{
	public:
		              CxTest_CxProcessInfo();
            ///< constructor
	    virtual      ~CxTest_CxProcessInfo();
	        ///< destructor

	    virtual bool  bUnit(const ulonglong_t cullCaseLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_Common_CxProcessInfoH
