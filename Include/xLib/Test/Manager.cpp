/**
 * \file  Manager.inl
 * \brief manage tests (Test)
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Manager.h"
#endif

#include <xLib/Core/Type.h>
#include <xLib/Core/String.h>
#include <xLib/Core/Functors.h>
#include <xLib/Core/Format.h>
#include <xLib/IO/Path.h>
#include <xLib/Log/Trace.h>
#include <xLib/System/ProcessInfo.h>
#include <xLib/System/User.h>
#include <xLib/Test/Unit.h>


xNAMESPACE_BEGIN2(xlib, test)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE
Manager::Manager(
    cint_t        &a_argsNum,
    cptr_ctchar_t  a_args[]
) :
    _data         (),
    _units        (),
    _isConstructed(false)
{
    _construct(a_argsNum, a_args);
}
//-------------------------------------------------------------------------------------------------
xINLINE
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
}
//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::add(
    Unit *a_unit
)
{
    xTEST_PTR(a_unit)

    if ( a_unit->data.name.empty() ) {
        a_unit->data.name = Type::name(*a_unit);
    }

    _units.push_back(a_unit);
}
//-------------------------------------------------------------------------------------------------
xINLINE bool_t
Manager::run()
{
    bool_t isUnitsPassed = true;

    xCHECK_DO(!_isConstructed,
        Trace() << xT("\nManager: not constructed. Stopped.");
        return false);

    xCHECK_DO(_data.isUseTracing,
        Trace()
            << Format::str(
                xT("\n")
                xT("Manager: start all...\n")
                xT("Manager: module path: {}\n")
                xT("Manager: all loops: {}, unit loops: {}, case loops: {}, unit number: {}"),
                Path::exe(), _data.allLoops, _data.unitLoops, _data.caseLoops, _units.size()));

    for (std::size_t i = 0; i < _data.allLoops; ++ i) {
        xFOR_EACH_CONST(units_t, it, _units) {
            xCHECK_DO(_data.isUseTracing, Trace() << xT("Manager: run unit ") << (*it)->data.name);

            bool_t bRv = (*it)->run();
            if (!bRv) {
                isUnitsPassed = false;
            } else {

            }
        } // for (_units)
    }

    xCHECK_DO(_data.isUseTracing, Trace() << xT("Manager: all successful done."));

    return isUnitsPassed;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE void_t
Manager::_construct(
    cint_t        &a_argsNum,
    cptr_ctchar_t  a_args[]
)
{
    bool_t bRv = false;

    // checks
    {
    #if xENV_UNIX
        User user;
        xCHECK_MSG_DO(user.isAdmin(), xT("Manager: can't run as root"), return);
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
                Trace() << xT("\nManager: unknown switches\n");
            } else {
                Trace()
                    << xT("\nManager usage: [binary_path] [is_tracing] [all_loops] [unit_loops]\n")
                       xT("  - binary_path (binary file path)\n")
                       xT("  - is_tracing  (is tracing)\n")
                       xT("  - all_loops   (loops for all tests)\n")
                       xT("  - unit_loops  (loops for unit test)\n")
                       xT("  - case_loops  (loops for case test)\n");
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
            Trace() << xT("\nManager: unknown switches\n");

            _isConstructed = false;

            break;
        }
    }

    xCHECK_DO(_data.isUseTracing,
        Trace()
            << Format::str(xT("\n\nManager: *** {} v.{} {} author: {} date: {} ***"),
                xLIB_NAME, xLIB_VERSION, xLIB_VERSION_SUFFIX, xLIB_AUTHOR, xLIB_DATE));
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, test)
