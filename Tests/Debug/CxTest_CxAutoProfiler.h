/****************************************************************************
* Class name:  CxTest_CxAutoProfiler
* Description: test CxAutoProfiler
* File name:   CxTest_CxAutoProfiler.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     14.04.2010 11:03:19
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxTest_CxAutoProfilerH
#define CxTest_CxAutoProfilerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Debug/CxAutoProfiler.h>
//---------------------------------------------------------------------------
class CxTest_CxAutoProfiler : public CxTest {
	public:
		CxTest_CxAutoProfiler();
	   ~CxTest_CxAutoProfiler();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxAutoProfiler (comment)
CxTest_CxAutoProfiler::CxTest_CxAutoProfiler() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxAutoProfiler (comment)
CxTest_CxAutoProfiler::~CxTest_CxAutoProfiler() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL 
CxTest_CxAutoProfiler::bUnit() {
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

	//-------------------------------------
	//CxAutoProfiler
	{
		for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
			CxAutoProfiler _apfAP(sGetWorkDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i], xT("%i"), 777);

			for (int x = 0; x < 1000/*00*/; ++ x) {
				for (int y = 0; y < 2000; ++ y) {
					int z = 0;

					z++; --z;
				}
			}
		}
	}

	//-------------------------------------
	//xAUTO_PERFORM_FUNC
	for (size_t i = 0; i < xARRAY_SIZE(pmPerformMode); ++ i) {
	    xAUTO_PROFILER_FUNC(sGetWorkDirPath() + CxConst::xSLASH + xT("__FuncLog.log"), pmPerformMode[i]);

		for (int x = 0; x < 1000/*00*/; ++ x) {
			for (int y = 0; y < 2000; ++ y) {
				int z = 0;

				z++; --z;
			}
		}
	}
	
	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxAutoProfilerH


