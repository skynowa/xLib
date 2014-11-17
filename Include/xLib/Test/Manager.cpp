/**
 * \file  Manager.inl
 * \brief manage tests (Test)
 */


#if !xOPTION_HEADER_ONLY
    #include "Manager.h"
#endif

#include <xLib/Core/Type.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Functors.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>
#include <xLib/Test/Unit.h>


xNAMESPACE_BEGIN2(xlib, test)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Manager::Manager(
    cbool_t &a_isUseTracing
) :
    _isUseTracing(a_isUseTracing),
    _tests       ()
{
    xCHECK_DO(_isUseTracing,
        Trace()
            << xT("\n\nTestManager: *** ") << xLIB_NAME
            << xT(" v.")                     << xLIB_VERSION << xT(" ") << xLIB_VERSION_SUFFIX
            << xT(" author: ")               << xLIB_AUTHOR
            << xT(" date: ")                 << xLIB_DATE
            << xT(" ***"));
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Manager::~Manager()
{
    std::for_each(_tests.begin(), _tests.end(), Delete());

    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: all tests destructed."));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::add(
    Unit *a_test
)
{
    xTEST_PTR(a_test)

    a_test->setName( Type::name(*a_test) );

    _tests.push_back(a_test);
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::run(
    culonglong_t &a_allLoops,
    culonglong_t &a_unitLoops,
    culonglong_t &a_caseLoops
)
{
    xTEST_NA(a_allLoops);
    xTEST_NA(a_unitLoops);
    xTEST_NA(a_caseLoops);

    xCHECK_DO(_isUseTracing, Trace() << xT("\nTestManager: start all tests..."));
    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: module path: ") << Path::exe());
    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: ")
                                       << xT("all loops: ")     << a_allLoops
                                       << xT(", unit loops: ")  << a_unitLoops
                                       << xT(", case loops: ")  << a_caseLoops
                                       << xT(", unit number: ") << _tests.size());

    for (ulonglong_t i = 0ULL; i < a_allLoops; ++ i) {
        xFOREACH_CONST(container_t, it, _tests) {
            xCHECK_DO(_isUseTracing, Trace() << xT("Manager: run test ") << (*it)->name());

            (*it)->run(a_unitLoops, a_caseLoops);
        }
    }

    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: all tests successful done."));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
