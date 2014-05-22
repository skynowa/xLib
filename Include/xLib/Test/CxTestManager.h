/**
 * \file  CxTestManager.h
 * \brief manage tests (CxTest)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Test/CxTest.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, test)

class CxTestManager
    /// manage tests (CxTest)
{
public:
    explicit    CxTestManager(cbool_t &isUseTracing);
        ///< constructor
    virtual    ~CxTestManager();
        ///< destructor

    void_t      add(CxTest *test);
        ///< add CxTest
    void_t      run(culonglong_t &allLoops, culonglong_t &unitLoops, culonglong_t &caseLoops);
        ///< run all tests

private:
    typedef std::vector<CxTest *> container_t;

    cbool_t     _isUseTracing;  ///< is use tracing
    container_t _tests;         ///< CxTest's container

    xNO_COPY_ASSIGN(CxTestManager)
};

xNAMESPACE_END2(xlib, test)
//-------------------------------------------------------------------------------------------------
#include "CxTestManager.inl"
