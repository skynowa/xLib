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
    _units       ()
{
    xCHECK_DO(_isUseTracing,
        Trace()
            << xT("\n\nManager: *** ") << xLIB_NAME
            << xT(" v.")               << xLIB_VERSION << xT(" ") << xLIB_VERSION_SUFFIX
            << xT(" author: ")         << xLIB_AUTHOR
            << xT(" date: ")           << xLIB_DATE
            << xT(" ***"));
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Manager::~Manager()
{
    std::for_each(_units.begin(), _units.end(), Delete());

    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: all destructed."));
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::add(
    Unit *a_unit
)
{
    xTEST_PTR(a_unit)

    a_unit->setName( Type::name(*a_unit) );

    _units.push_back(a_unit);
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

    xCHECK_DO(_isUseTracing, Trace() << xT("\nTestManager: start all..."));
    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: module path: ") << Path::exe());
    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: ")
                                     << xT("all loops: ")     << a_allLoops
                                     << xT(", unit loops: ")  << a_unitLoops
                                     << xT(", case loops: ")  << a_caseLoops
                                     << xT(", unit number: ") << _units.size());

    for (ulonglong_t i = 0ULL; i < a_allLoops; ++ i) {
        xFOREACH_CONST(units_t, it, _units) {
            xCHECK_DO(_isUseTracing, Trace() << xT("Manager: run unit ") << (*it)->name());

            (*it)->run(a_unitLoops, a_caseLoops);
        }
    }

    xCHECK_DO(_isUseTracing, Trace() << xT("Manager: all successful done."));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
