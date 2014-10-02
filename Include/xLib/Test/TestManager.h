/**
 * \file  TestManager.h
 * \brief manage tests (Test)
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
#include <xLib/Test/Test.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, test)

class UnitTest;

class TestManager
    /// manage tests (Test)
{
public:
    explicit    TestManager(cbool_t &isUseTracing);
        ///< constructor
    virtual    ~TestManager();
        ///< destructor

    void_t      add(UnitTest *test);
        ///< add Test
    void_t      run(culonglong_t &allLoops, culonglong_t &unitLoops, culonglong_t &caseLoops);
        ///< run all tests

private:
    typedef std::vector<UnitTest *> container_t;

    cbool_t     _isUseTracing;  ///< is use tracing
    container_t _tests;         ///< Test's container

    xNO_COPY_ASSIGN(TestManager)
};

xNAMESPACE_END2(xlib, test)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "TestManager.cpp"
#endif
