/**
 * \file  CxTestManager.h
 * \brief manage tests (CxTest)
 */


#ifndef xLib_Debug_CxTestManagerH
#define xLib_Debug_CxTestManagerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTestManager :
    public CxNonCopyable
    /// manage tests (CxTest)
{
	public:
				   CxTestManager(const BOOL cbIsUseTracing);
		virtual   ~CxTestManager();

        BOOL       bAdd         (CxTest *pvtTest, const std::tstring &csTestName = CxConst::xSTR_EMPTY);
        BOOL       bRun         (const ULONGLONG cullAllLoops, const ULONGLONG cullUnitLoops, const ULONGLONG cullBlockLoops);

        //TODO: not enough RAM
        //TODO: not enough HDD
        //TODO: busy CPU
        //TODO: every macros wrapped by try-catch

    private:
        typedef std::vector<CxTest *> TContainer;

        BOOL       _m_bRes;
        const BOOL _m_cbIsUseTracing;
        TContainer _m_ctnTests;
};
//---------------------------------------------------------------------------
#endif //xLib_CxTestManager.H
