/****************************************************************************
* Class name:  CxTest_CxProfiler
* Description: test CxProfiler
* File name:   CxTest_CxProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Debug/CxTest_CxProfiler.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxProfiler
CxTest_CxProfiler::CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxProfiler
CxTest_CxProfiler::~CxTest_CxProfiler() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxProfiler::bUnit() {
	const CxProfiler::EMode pmPerformMode[] = {
	        CxProfiler::pmStdClock,
	        CxProfiler::pmDateTime,
        #if defined(xOS_WIN)
	        CxProfiler::pmTickCount,
	        CxProfiler::pmPerformanceCount,
	        CxProfiler::pmThreadTimes,
        #elif defined(xOS_LINUX)
	        CxProfiler::pmGetTimeOfDay
        #endif
	};

	for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
		const tString csFilePath = sGetWorkDirPath() + CxConst::xSLASH + xT("___Log.log");

		CxProfiler pfP(pmPerformMode[i]);

		m_bRes = pfP.bSetLogPath(csFilePath);
		xASSERT_NOT_EQUAL(FALSE, m_bRes);

		m_sRes = pfP.sGetLogPath();
		xASSERT_EQUAL(csFilePath, m_sRes);

		m_bRes = pfP.bStart();
		xASSERT_NOT_EQUAL(FALSE, m_bRes);

		for (size_t i = 0; i < 10; ++ i) {
			for (size_t j = 0; j < 2; ++ j) {
				size_t x = 0;

				x++; --x; x = x / 3;
			}

			pfP.bPulse(xT("Variable i: %zu"), i);
			xASSERT_NOT_EQUAL(FALSE, m_bRes);
		}

		pfP.bStop(xT(""));
	    xASSERT_NOT_EQUAL(FALSE, m_bRes);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
