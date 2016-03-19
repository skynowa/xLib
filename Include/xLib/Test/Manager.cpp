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
    _data (),
    _units()
{
    // checks
    {
    #if xENV_UNIX
        SystemInfo info;
        xCHECK_MSG_DO(info.isUserAdmin(), xT("xLib_test: Can't run as root"), return);
    #endif
    }

    // parse params
    {
        std::vec_tstring_t args;

        ProcessInfo info;
        info.setProcessId(Process::currentId());
        info.commandLine(&args);

        Trace() << xTRACE_VAR(a_argsNum);
        Trace() << xTRACE_VAR(args.size());
        Trace() << xTRACE_VAR(args);

        if (a_argsNum == 1) {
            // OK, run tests with default params
        }
        else if (a_argsNum == 2) {
            // usage
            bool_t bRv = StringCI::compare(xT("-h"),     args.at(1)) ||
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

            return;
        }
        else if (a_argsNum == 5) {
            // params
            _data.isUseTracing = String::cast<bool_t>     ( args.at(1) );
            _data.allLoops     = String::cast<std::size_t>( args.at(2) );
            _data.unitLoops    = String::cast<std::size_t>( args.at(3) );
            _data.caseLoops    = String::cast<std::size_t>( args.at(4) );
        }
        else {
            // fail
            std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            return;
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
Manager::Manager(
    cManagerData &a_data
) :
    _data (a_data),
    _units()
{
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
    xCHECK_DO(_data.isUseTracing,
        Trace() << xT("\nTestManager: start all...");
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

xNAMESPACE_END2(xlib, test)
