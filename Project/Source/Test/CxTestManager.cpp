/**
 * \file  CxTestManager.cpp
 * \brief manage tests (CxTest)
 */


#include <xLib/Test/CxTestManager.h>

#include <xLib/Common/CxType.h>
#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*explicit*/
CxTestManager::CxTestManager(
    const bool a_cbIsUseTracing
) :
    _m_cbIsUseTracing(a_cbIsUseTracing),
    _m_ctnTests      ()
{
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("\n\nCxTestManager: *** xLib v.%s (author: %s date: %s) ***"), xLIB_VERSION, xLIB_AUTHOR, xLIB_DATE));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//---------------------------------------------------------------------------
/* virtual */
CxTestManager::~CxTestManager() {
    xFOREACH(container_t, it, _m_ctnTests) {
        /*CxUtils::*/xPTR_DELETE(*it);
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests destructed.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//---------------------------------------------------------------------------
bool
CxTestManager::bAdd(
    CxTest               *a_pvtTest,
    const std::tstring_t &a_csTestName /* = CxConst::xSTR_EMPTY */
)
{
    /*DEBUG*/
    /*DEBUG*/xTEST_PTR(a_pvtTest)

    a_pvtTest->vSetName( CxType::sGetName(*a_pvtTest) );

    _m_ctnTests.push_back(a_pvtTest);

    #if xTEMP_DISABLED
        xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: added test \"%s\""), a_pvtTest->sGetName().c_str()));
    #endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxTestManager::bRun(
    const ulonglong_t &a_cullAllLoops,
    const ulonglong_t &a_cullUnitLoops,
    const ulonglong_t &a_cullCaseLoops
)
{
    /*DEBUG*/

    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("CxTestManager: start all tests...")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: module path: %s"), CxPath::sGetExe().c_str()));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: all loops: %") xPR_I64u xT(", unit loops: %") xPR_I64u xT(", block loops: %") xPR_I64u xT(", unit number: %")  xPR_SIZET xT("\n"), a_cullAllLoops, a_cullUnitLoops, a_cullCaseLoops, _m_ctnTests.size()));

    for (ulonglong_t i = 0ULL; i < a_cullAllLoops; ++ i) {
        xFOREACH_CONST(container_t, it, _m_ctnTests) {
            xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: run test \"%s\""), (*it)->sGetName().c_str()));

            (*it)->vRun(a_cullUnitLoops, a_cullCaseLoops);
            // TODO: xTEST_MSG_EQ(true, bRv, CxString::sFormat(xT("CxTestManager: test \"%s\" not complete"), (*it)->sGetName().c_str()));

            //xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("...Ok")));
        }
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests successful done.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("\n")));

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
