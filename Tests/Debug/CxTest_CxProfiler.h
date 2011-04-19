/****************************************************************************
* Class name:  CxTest_CxProfiler
* Description: test CxProfiler
* File name:   CxTest_CxProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxProfilerH
#define CxTest_CxProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxProfiler.h>
//---------------------------------------------------------------------------
class CxTest_CxProfiler : public CxTest {
	public:
		CxTest_CxProfiler();
		virtual     ~CxTest_CxProfiler();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxProfiler (constructor)
CxTest_CxProfiler::CxTest_CxProfiler() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxProfiler (destructor)
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL
CxTest_CxProfiler::bUnit() {
	const CxProfiler::EMode pmPerformMode[] = {
	        CxProfiler::pmClock,
	        CxProfiler::pmTime,
        #if defined(xOS_WIN)
	        CxProfiler::pmTickCount,
	        CxProfiler::pmPerformanceCount,
	        CxProfiler::pmThreadTimes,
        #elif defined(xOS_LINUX)
	        CxProfiler::pmGetTimeOfDay
        #endif
	};

	for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
		CxProfiler pfP(sGetWorkDirPath() + CxConst::xSLASH + xT("___Log.log"), pmPerformMode[i]);

		pfP.bStart();

		////for (int i = 0; i < 100; i ++) {
		for (int i = 0; i < 1000/*00*/; ++ i) {
			for (int i = 0; i < 1000/*00*/; ++ i) {
				int x = 0;

				x++; --x;
			}
		}
			////::Sleep(2000);
			////pfP.bPulse(i);
		////}

		pfP.bStop(xT(""));
	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxProfilerH

