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
    int_t    a_argsNum,
    tchar_t *a_args[],
    cbool_t &a_isUseTracing
) :
    _isUseTracing(a_isUseTracing),
    _units       ()
{
    xUNUSED(a_argsNum);
    xUNUSED(a_args);

    // checks
    {
    #if xENV_UNIX
        SystemInfo info;
        xCHECK_MSG_DO(info.isUserAdmin(), xT("xLib_test: Can't run as root"), return);
    #endif
    }

    // options (default)
    bool_t      isUseTracing = true;
    ulonglong_t allLoops     = 1ULL;
    ulonglong_t unitLoops    = 1ULL;
    ulonglong_t caseLoops    = 1ULL;
    {
        std::vec_tstring_t args;

        ProcessInfo info;
        info.setProcessId(Process::currentId());
        info.commandLine(&args);

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
            // addition params
            isUseTracing = String::cast<bool_t>     ( args.at(1) );
            allLoops     = String::cast<ulonglong_t>( args.at(2) );
            unitLoops    = String::cast<ulonglong_t>( args.at(3) );
            caseLoops    = String::cast<ulonglong_t>( args.at(4) );
        }
        else {
            // fail
            std::tcout << xT("\nxLib_test: unknown switches\n") << std::endl;
            return;
        }
    }

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
