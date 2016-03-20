/**
 * \file  Manager.inl
 * \brief manage tests (Test)
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Manager.h"
#endif

#include <xLib/Core/Type.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Functors.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/SystemInfo.h>
#include <xLib/Test/Unit.h>


xNAMESPACE_BEGIN2(xlib, test)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Manager::Manager(
    cint_t   &a_argsNum,
    ctchar_t *a_args[]
) :
    _data         (),
    _units        (),
    _isConstructed(false)
{
    _construct(a_argsNum, a_args);
}
//-------------------------------------------------------------------------------------------------
Manager::Manager(
    cManagerData &a_data
) :
    _data         (a_data),
    _units        (),
    _isConstructed(false)
{
    _construct(0, xPTR_NULL);
}
//-------------------------------------------------------------------------------------------------
/* virtual */
xINLINE
Manager::~Manager()
{
    std::for_each(_units.begin(), _units.end(), Delete());

    xCHECK_DO(_data.isUseTracing, Trace() << xT("Manager: all destructed."));
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
Manager::run()
{
    xCHECK_DO(!_isConstructed,
        Trace() << xT("\nManager: not constructed. Stopped.");
        return);

    xCHECK_DO(_data.isUseTracing,
        Trace() << xT("\n");
        Trace() << xT("Manager: start all...");
        Trace() << xT("Manager: module path: ") << Path::exe();
        Trace() << xT("Manager: ")
                << xT("all loops: ")     << _data.allLoops
                << xT(", unit loops: ")  << _data.unitLoops
                << xT(", case loops: ")  << _data.caseLoops
                << xT(", unit number: ") << _units.size());

    for (std::size_t i = 0; i < _data.allLoops; ++ i) {
        xFOREACH_CONST(units_t, it, _units) {
            xCHECK_DO(_data.isUseTracing, Trace() << xT("Manager: run unit ") << (*it)->name());

            (*it)->run(_data.unitLoops, _data.caseLoops);
        }
    }

    xCHECK_DO(_data.isUseTracing, Trace() << xT("Manager: all successful done."));
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::_construct(
    cint_t   &a_argsNum,
    ctchar_t *a_args[]
)
{
    bool_t bRv = false;

    // checks
    {
    #if xENV_UNIX
        SystemInfo info;
        xCHECK_MSG_DO(info.isUserAdmin(), xT("xLib_test: Can't run as root"), return);
    #endif
    }

    // parse params
    if (a_args == xPTR_NULL) {
        _isConstructed = true;
    } else {
        std::vec_tstring_t args;
        ProcessInfo::commandLine(a_argsNum, a_args, &args);
        xTEST_EQ(a_argsNum, (int_t)args.size());

        switch ( args.size() ) {
        case 1:
            // OK - default params
            _isConstructed = true;

            break;
        case 2:
            // usage
            bRv = StringCI::compare(xT("-h"),     args.at(1)) ||
                  StringCI::compare(xT("--help"), args.at(1));
            if (!bRv) {
                std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            } else {
                std::tcout << xT("\nUsage: ./xLib_test [is_tracing] [all_loops] [unit_loops]\n")
                              xT("  - xLib_test  (binary file path)\n")
                              xT("  - is_tracing (is tracing)\n")
                              xT("  - all_loops  (loops for all tests)\n")
                              xT("  - unit_loops (loops for unit test)\n")
                              xT("  - case_loops (loops for case test)\n") << std::endl;
            }

            _isConstructed = false;

            break;
        case 5:
            // params
            _data.isUseTracing = String::cast<bool_t>     ( args.at(1) );
            _data.allLoops     = String::cast<std::size_t>( args.at(2) );
            _data.unitLoops    = String::cast<std::size_t>( args.at(3) );
            _data.caseLoops    = String::cast<std::size_t>( args.at(4) );

            _isConstructed = true;

            break;
        default:
            // fail
            std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;

            _isConstructed = false;

            break;
        }
    }

    xCHECK_DO(_data.isUseTracing,
        Trace()
            << xT("\n\nManager: *** ") << xLIB_NAME
            << xT(" v.")               << xLIB_VERSION << xT(" ") << xLIB_VERSION_SUFFIX
            << xT(" author: ")         << xLIB_AUTHOR
            << xT(" date: ")           << xLIB_DATE
            << xT(" ***"));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
