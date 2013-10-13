/**
 * \file  CxTestManager.cpp
 * \brief manage tests (CxTest)
 */


#include <xLib/Test/CxTestManager.h>

#include <xLib/Core/CxType.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/*explicit*/
CxTestManager::CxTestManager(
    cbool_t &a_cbIsUseTracing
) :
    _m_cbIsUseTracing(a_cbIsUseTracing),
    _m_ctnTests      ()
{
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("\n\nCxTestManager: *** %s v.%s %s (author: %s date: %s) ***"),
                                         xLIB_NAME, xLIB_VERSION, xLIB_VERSION_SUFFIX, xLIB_AUTHOR, xLIB_DATE));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
}
//------------------------------------------------------------------------------
/* virtual */
CxTestManager::~CxTestManager()
{
    xFOREACH(container_t, it, _m_ctnTests) {
        xPTR_DELETE(*it);
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests destructed.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("\n")));
}
//------------------------------------------------------------------------------
void_t
CxTestManager::add(
    CxTest *a_pvtTest
)
{
    xTEST_PTR(a_pvtTest)

    a_pvtTest->setName( CxType::name(*a_pvtTest) );

    _m_ctnTests.push_back(a_pvtTest);

#if xTEMP_DISABLED
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: added test \"%s\""), a_pvtTest->name().c_str()));
#endif
}
//------------------------------------------------------------------------------
void_t
CxTestManager::run(
    culonglong_t &a_cullAllLoops,
    culonglong_t &a_cullUnitLoops,
    culonglong_t &a_cullCaseLoops
)
{
    xTEST_NA(a_cullAllLoops);
    xTEST_NA(a_cullUnitLoops);
    xTEST_NA(a_cullCaseLoops);

    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("\n")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE (xT("CxTestManager: start all tests...")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: module path: %s"), CxPath::exe().c_str()));
    xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: all loops: %") xPR_I64u
                                         xT(", unit loops: %") xPR_I64u
                                         xT(", case loops: %") xPR_I64u
                                         xT(", unit number: %") xPR_SIZET xT("\n"),
                                         a_cullAllLoops, a_cullUnitLoops, a_cullCaseLoops, _m_ctnTests.size()));

    for (ulonglong_t i = 0ULL; i < a_cullAllLoops; ++ i) {
        xFOREACH_CONST(container_t, it, _m_ctnTests) {
            xCHECK_DO(_m_cbIsUseTracing, xTRACEV(xT("CxTestManager: run test \"%s\""), (*it)->name().c_str()));

            (*it)->run(a_cullUnitLoops, a_cullCaseLoops);
            // TODO: xTEST_MSG_EQ(true, bRv, CxString::format(xT("CxTestManager: test \"%s\" not complete"), (*it)->sName().c_str()));

            //xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("...Ok")));
        }
    }

    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("CxTestManager: all tests successful done.")));
    xCHECK_DO(_m_cbIsUseTracing, xTRACE(xT("\n")));
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
