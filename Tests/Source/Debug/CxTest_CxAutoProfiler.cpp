/****************************************************************************
* Class name:  CxTest_CxAutoProfiler
* Description: test CxAutoProfiler
* File name:   CxTest_CxAutoProfiler.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxAutoProfiler (comment)
CxTest_CxAutoProfiler::CxTest_CxAutoProfiler() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxAutoProfiler (comment)
CxTest_CxAutoProfiler::~CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxAutoProfiler::bUnit() {
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

	//-------------------------------------
	//CxAutoProfiler
	{
		for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
			CxAutoProfiler _apfAP(sGetWorkDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i], xT("%i"), 777);

			for (size_t x = 0; x < 1000; ++ x) {
				for (size_t y = 0; y < 2000; ++ y) {
					size_t z = 0;

					z++; --z; z = z / 7;
				}
			}
		}
	}

	//-------------------------------------
	//xAUTO_PERFORM_FUNC
	for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
	    xAUTO_PROFILER_FUNC(sGetWorkDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i]);

		for (size_t x = 0; x < 100; ++ x) {
			for (size_t y = 0; y < 100; ++ y) {
				size_t z = 0;

				z++; --z; z = z / 13;
			}
		}
	}

	return TRUE;
}
//---------------------------------------------------------------------------
