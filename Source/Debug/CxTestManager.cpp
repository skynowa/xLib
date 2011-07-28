/****************************************************************************
* Class name:  CxTestManager
* Description: manage tests (CxTest)
* File name:   CxTestManager.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     18.07.2011
*
*****************************************************************************/


#include <xLib/Debug/CxTestManager.h>


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxTestManager
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
//DONE: ~CxTestManager
/*virtual*/
CxTestManager::~CxTestManager() {
    for (TContainer::iterator it = _m_ctnTests.begin(); it != _m_ctnTests.end(); ++ it) {
        /*CxMacros::*/xPTR_DELETE(*it);
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests deleted.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//---------------------------------------------------------------------------
//DONE: bAdd (new CxTest)
#if defined(xCOMPILER_GNUC) || defined(xCOMPILER_MINGW32)
    #include <cxxabi.h> //abi::__cxa_demangle
#endif

BOOL
CxTestManager::bAdd(
    CxTest        *pvtTest,
    const tString &csTestName /*= CxConst::xSTR_EMPTY*/
)
{
    /*DEBUG*/
    /*DEBUG*/xASSERT_RET(NULL != pvtTest, FALSE)

    //TODO: sClassName must move to CxObject
    tString sClassName;
    if (csTestName == CxConst::xSTR_EMPTY) {
        #if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_GNUC)
            INT  iStatus      = - 1;
            char *pszRealName = NULL;

            pszRealName = abi::__cxa_demangle(typeid(*pvtTest).name(), 0, 0, &iStatus);
            sClassName  = (NULL != pszRealName) ? (pszRealName) : xT("<unknown test name>");
            xBUFF_FREE(pszRealName);
        #else
            sClassName.assign(typeid(*pvtTest).name());
        #endif
    } else {
        sClassName.assign(csTestName);
    }

    pvtTest->bSetName(sClassName);
    /*DEBUG*/// n/a

    _m_ctnTests.push_back(pvtTest);

    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: added test %s"), pvtTest->sGetName().c_str()));

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bRun (run tests)
BOOL
CxTestManager::bRun(
    const ULONGLONG cullAllLoops,
    const ULONGLONG cullUnitLoops
)
{
    /*DEBUG*/

    BOOL bRes = FALSE;

    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("CxTestManager: start all tests...")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: module path: %s"), CxPath::sGetExe().c_str()));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: all loops: %"xPR_I64u" unit loops: %"xPR_I64u"\n"), cullAllLoops, cullUnitLoops));

    for (ULONGLONG i = 0; i < cullAllLoops; ++ i) {
        for (TContainer::iterator it = _m_ctnTests.begin(); it != _m_ctnTests.end(); ++ it) {
            xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: run test %s"), (*it)->sGetName().c_str()));

            bRes = (*it)->bRun(cullUnitLoops);
            xASSERT_MSG_RET(FALSE != bRes, CxString::sFormat(xT("CxTestManager: test (%s) not complete"), (*it)->sGetName().c_str()), FALSE);
        }
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests successful done.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));

    return TRUE;
}
//---------------------------------------------------------------------------
