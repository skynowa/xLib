/**
 * \file  CxTestManager.cpp
 * \brief manage tests (CxTest)
 */


#include <xLib/Core/CxType.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Log/CxTrace.h>


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxTestManager::CxTestManager(
    cbool_t &a_isUseTracing
) :
    _isUseTracing(a_isUseTracing),
    _tests       ()
{
    xCHECK_DO(_isUseTracing,
        CxTrace()
            << xT("\n\nCxTestManager: *** ") << xLIB_NAME
            << xT(" v.")                     << xLIB_VERSION << xT(" ") << xLIB_VERSION_SUFFIX
            << xT(" author: ")               << xLIB_AUTHOR
            << xT(" date: ")                 << xLIB_DATE
            << xT(" ***"));
}
//-------------------------------------------------------------------------------------------------
/* virtual */
inline
CxTestManager::~CxTestManager()
{
    std::for_each(_tests.begin(), _tests.end(), functors::Delete());

    xCHECK_DO(_isUseTracing, CxTrace() << xT("CxTestManager: all tests destructed."));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTestManager::add(
    CxTest *a_test
)
{
    xTEST_PTR(a_test)

    a_test->setName( CxType::name(*a_test) );

    _tests.push_back(a_test);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxTestManager::run(
    culonglong_t &a_allLoops,
    culonglong_t &a_unitLoops,
    culonglong_t &a_caseLoops
)
{
    xTEST_NA(a_allLoops);
    xTEST_NA(a_unitLoops);
    xTEST_NA(a_caseLoops);

    xCHECK_DO(_isUseTracing, CxTrace() << xT("\nCxTestManager: start all tests..."));
    xCHECK_DO(_isUseTracing, CxTrace() << xT("CxTestManager: module path: ") << CxPath::exe());
    xCHECK_DO(_isUseTracing, CxTrace() << xT("CxTestManager: ")
                                       << xT("all loops: ")     << a_allLoops
                                       << xT(", unit loops: ")  << a_unitLoops
                                       << xT(", case loops: ")  << a_caseLoops
                                       << xT(", unit number: ") << _tests.size());

    for (ulonglong_t i = 0ULL; i < a_allLoops; ++ i) {
        xFOREACH_CONST(container_t, it, _tests) {
            xCHECK_DO(_isUseTracing, CxTrace() << xT("CxTestManager: run test ") << (*it)->name());

            (*it)->run(a_unitLoops, a_caseLoops);
        }
    }

    xCHECK_DO(_isUseTracing, CxTrace() << xT("CxTestManager: all tests successful done."));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
