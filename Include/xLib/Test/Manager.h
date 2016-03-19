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

struct ManagerData
{
    bool_t      isUseTracing;
    std::size_t allLoops;
    std::size_t unitLoops;
    std::size_t caseLoops;

    ManagerData() :
        isUseTracing(false),
        allLoops    (1),
        unitLoops   (1),
        caseLoops   (1)
    {}
};
xTYPEDEF_CONST(ManagerData);

class Unit;

class Manager
    /// manager
{
public:
             Manager(cint_t &argsNum, ctchar_t *args[]);
        ///< constructor
             Manager(cManagerData &data);
        ///< constructor
    virtual ~Manager();
        ///< destructor

    void_t   add(Unit *unit);
        ///< add unit
    void_t   run();
        ///< run all units

private:
    typedef std::vector<Unit *> units_t;

    ManagerData _data;
    units_t  _units;         ///< units

    xNO_COPY_ASSIGN(Manager)
};

xNAMESPACE_END2(xlib, test)
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "Manager.cpp"
#endif
