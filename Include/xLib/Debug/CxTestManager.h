/****************************************************************************
* Class name:  CxTestManager
* Description: manage tests (CxTest)
* File name:   CxTestManager.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     18.07.2011
*
*****************************************************************************/


#ifndef xLib_Debug_CxTestManagerH
#define xLib_Debug_CxTestManagerH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
//---------------------------------------------------------------------------
class CxTestManager :
    public CxNonCopyable
{
	public:
				   CxTestManager(const BOOL cbIsUseTracing);
		virtual   ~CxTestManager();

        BOOL       bAdd         (CxTest *pvtTest, const tString &csTestName = CxConst::xSTR_EMPTY);
        BOOL       bRun         (const ULONGLONG cullTimesForAll, const ULONGLONG  ullTimesForSingle);

    private:
        typedef std::vector<CxTest *> TContainer;

        BOOL       _m_bRes;
        const BOOL _m_cbIsUseTracing;
        ULONGLONG  _m_ullTimesForAll;
        ULONGLONG  _m_ullTimesForSingle;
        TContainer _m_ctnTests;
};
//---------------------------------------------------------------------------
#endif //xLib_CxTestManager.H
