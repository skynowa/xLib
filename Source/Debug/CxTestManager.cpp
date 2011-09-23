/**
 * \file  CxTestManager.cpp
 * \brief manage tests (CxTest)
 */


#include <xLib/Debug/CxTestManager.h>

#include <xLib/Common/CxType.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*explicit*/
CxTestManager::CxTestManager(
    const BOOL cbIsUseTracing
) :
    _m_bRes          (FALSE),
    _m_cbIsUseTracing(cbIsUseTracing),
    _m_ctnTests      ()
{
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("\n\nCxTestManager: *** xLib v.%s (author: %s date: %s) ***"), xLIB_VERSION, xLIB_AUTHOR, xLIB_DATE));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//---------------------------------------------------------------------------
/*virtual*/
CxTestManager::~CxTestManager() {
    for (TContainer::iterator it = _m_ctnTests.begin(); it != _m_ctnTests.end(); ++ it) {
        /*CxMacros::*/xPTR_DELETE(*it);
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests destructed.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//---------------------------------------------------------------------------
BOOL
CxTestManager::bAdd(
    CxTest        *pvtTest,
    const std::tstring &csTestName /*= CxConst::xSTR_EMPTY*/
)
{
    /*DEBUG*/
    /*DEBUG*/xASSERT_RET(NULL != pvtTest, FALSE)

    pvtTest->bSetName( CxType::sGetName(*pvtTest) );
    /*DEBUG*/// n/a

    _m_ctnTests.push_back(pvtTest);

    #if xTEMP_DISABLED
        xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: added test \"%s\""), pvtTest->sGetName().c_str()));
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxTestManager::bRun(
    const ULONGLONG cullAllLoops,
    const ULONGLONG cullUnitLoops,
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("CxTestManager: start all tests...")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: module path: %s"), CxPath::sGetExe().c_str()));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: all loops: %") xPR_I64u xT(", unit loops: %") xPR_I64u xT(", block loops: %") xPR_I64u xT(", unit number: %")  xPR_SIZET xT("\n"), cullAllLoops, cullUnitLoops, cullBlockLoops, _m_ctnTests.size()));

    for (ULONGLONG i = 0ULL; i < cullAllLoops; ++ i) {
        for (TContainer::iterator it = _m_ctnTests.begin(); it != _m_ctnTests.end(); ++ it) {
            xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: run test \"%s\""), (*it)->sGetName().c_str()));

            bRes = (*it)->bRun(cullUnitLoops, cullBlockLoops);
            xASSERT_MSG_RET(FALSE != bRes, CxString::sFormat(xT("CxTestManager: test \"%s\" not complete"), (*it)->sGetName().c_str()), FALSE);

            //xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("...Ok")));
        }
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests successful done.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("\n")));

    return TRUE;
}
//---------------------------------------------------------------------------
