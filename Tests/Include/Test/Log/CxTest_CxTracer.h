/**
 * \file   CxTest_CxTracer.h
 * \brief  test CxTracer
 */


#ifndef CxTest_Log_CxTracerH
#define CxTest_Log_CxTracerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Log/CxTracer.h>
//---------------------------------------------------------------------------
class CxTest_CxTracer :
    public CxTest
{
	public:
		              CxTest_CxTracer();
            ///< constructor
	    virtual      ~CxTest_CxTracer();
	        ///< destructor

	    virtual bool  bUnit(const ulonglong_t cullBlockLoops);
	        ///< unit test

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_Log_CxTracerH
