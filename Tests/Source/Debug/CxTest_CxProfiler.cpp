/****************************************************************************
* Class name:  CxTest_CxProfiler
* Description: test CxProfiler
* File name:   CxTest_CxProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxProfiler (constructor)
CxTest_CxProfiler::CxTest_CxProfiler() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxProfiler (destructor)
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
		xASSERT(FALSE != m_bRes);

		m_sRes = pfP.sGetLogPath();
		xASSERT_EQUAL(csFilePath, m_sRes);

		pfP.bStart();
		xASSERT(FALSE != m_bRes);

		for (size_t i = 0; i < 10; ++ i) {
			for (size_t j = 0; j < 10; ++ j) {
				size_t x = 0;

				x++; --x; x = x / 3;
			}

			pfP.bPulse(xT("Variable i: %zu"), i);
			xASSERT(FALSE != m_bRes);
		}

		pfP.bStop(xT(""));
	    xASSERT(FALSE != m_bRes);
	}

    return TRUE;
}
//---------------------------------------------------------------------------
