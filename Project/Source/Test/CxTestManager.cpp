/**
 * \file  CxTestManager.cpp
 * \brief manage tests (CxTest)
 */


#include <xLib/Test/CxTestManager.h>

#include <xLib/Core/CxType.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO
CxTestManager::CxTestManager(
    cbool_t &a_isUseTracing
) :
    _isUseTracing(a_isUseTracing),
    _tests      ()
{
    xCHECK_DO(_isUseTracing, xTRACEV(xT("\n\nCxTestManager: *** %s v.%s %s (author: %s date: %s) ***"),
                                         xLIB_NAME, xLIB_VERSION, xLIB_VERSION_SUFFIX, xLIB_AUTHOR, xLIB_DATE));
    xCHECK_DO(_isUseTracing, xTRACE (xT("\n")));
}
//------------------------------------------------------------------------------
/* virtual */
xINLINE_HO
CxTestManager::~CxTestManager()
{
    xFOREACH(container_t, it, _tests) {
        xPTR_DELETE(*it);
    }

    xCHECK_DO(_isUseTracing, xTRACE(xT("CxTestManager: all tests destructed.")));
    xCHECK_DO(_isUseTracing, xTRACE(xT("\n")));
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTestManager::add(
    CxTest *a_test
)
{
    xTEST_PTR(a_test)

    a_test->setName( CxType::name(*a_test) );

    _tests.push_back(a_test);

#if xTEMP_DISABLED
    xCHECK_DO(_isUseTracing, xTRACEV(xT("CxTestManager: added test \"%s\""), a_test->name().c_str()));
#endif
}
//------------------------------------------------------------------------------
xINLINE_HO void_t
CxTestManager::run(
    culonglong_t &a_allLoops,
    culonglong_t &a_unitLoops,
    culonglong_t &a_caseLoops
)
{
    xTEST_NA(a_allLoops);
    xTEST_NA(a_unitLoops);
    xTEST_NA(a_caseLoops);

    xCHECK_DO(_isUseTracing, xTRACE (xT("\n")));
    xCHECK_DO(_isUseTracing, xTRACE (xT("CxTestManager: start all tests...")));
    xCHECK_DO(_isUseTracing, xTRACEV(xT("CxTestManager: module path: %s"), CxPath::exe().c_str()));
    xCHECK_DO(_isUseTracing, xTRACEV(xT("CxTestManager: all loops: %") xPR_I64u
                                         xT(", unit loops: %") xPR_I64u
                                         xT(", case loops: %") xPR_I64u
                                         xT(", unit number: %") xPR_SIZET xT("\n"),
                                         a_allLoops, a_unitLoops, a_caseLoops, _tests.size()));

    for (ulonglong_t i = 0ULL; i < a_allLoops; ++ i) {
        xFOREACH_CONST(container_t, it, _tests) {
            xCHECK_DO(_isUseTracing, xTRACEV(xT("CxTestManager: run test \"%s\""), (*it)->name().c_str()));

            (*it)->run(a_unitLoops, a_caseLoops);
            // TODO: xTEST_MSG_EQ(true, bRv, CxString::format(xT("CxTestManager: test \"%s\" not complete"), (*it)->sName().c_str()));

            //xCHECK_DO(_isUseTracing, xTRACE(xT("...Ok")));
        }
    }

    xCHECK_DO(_isUseTracing, xTRACE(xT("CxTestManager: all tests successful done.")));
    xCHECK_DO(_isUseTracing, xTRACE(xT("\n")));
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
