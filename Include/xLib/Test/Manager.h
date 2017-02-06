/**
 * \file  Manager.h
 * \brief manage tests (Test)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, test)

struct ManagerData
    /// manager data
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
             Manager(cint_t &argsNum, cptr_ctchar_t args[]);
        ///< constructor
    explicit Manager(cManagerData &data = cManagerData());
        ///< constructor
    virtual ~Manager();
        ///< destructor

    void_t   add(Unit *unit);
        ///< add unit
    bool_t   run();
        ///< run all units

private:
    typedef std::vector<Unit *> units_t;

    ManagerData _data;          ///< data
    units_t     _units;         ///< units
    bool_t      _isConstructed; ///< is object constructed

    void_t   _construct(cint_t &a_argsNum, cptr_ctchar_t a_args[]);

    xNO_COPY_ASSIGN(Manager)
};

xNAMESPACE_END2(xl, test)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Manager.cpp"
#endif
