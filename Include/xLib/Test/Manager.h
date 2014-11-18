/**
 * \file  Manager.h
 * \brief manage tests (Test)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, test)

class Unit;

class Manager
    /// manager
{
public:
    explicit Manager(cbool_t &isUseTracing);
        ///< constructor
    virtual ~Manager();
        ///< destructor

    void_t   add(Unit *unit);
        ///< add unit
    void_t   run(culonglong_t &allLoops, culonglong_t &unitLoops, culonglong_t &caseLoops);
        ///< run all units

private:
    typedef std::vector<Unit *> units_t;

    cbool_t  _isUseTracing;  ///< is use tracing
    units_t  _units;         ///< units

    xNO_COPY_ASSIGN(Manager)
};

xNAMESPACE_END2(xlib, test)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Manager.cpp"
#endif
