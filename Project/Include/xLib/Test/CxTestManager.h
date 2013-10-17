/**
 * \file  CxTestManager.h
 * \brief manage tests (CxTest)
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxConst.h>
#include <xLib/Test/CxTest.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTestManager :
    private CxNonCopyable
    /// manage tests (CxTest)
{
public:
    explicit    CxTestManager(cbool_t &isUseTracing);
        ///< constructor
    virtual    ~CxTestManager();
        ///< destructor

    void_t      add(CxTest *test);
        ///< add CxTest
    void_t      run(culonglong_t &allLoops, culonglong_t &unitLoops,
                    culonglong_t &caseLoops);
        ///< run all tests

private:
    typedef std::vector<CxTest *> container_t;

    cbool_t     _isUseTracing;   ///< is use tracing
    container_t _tests;         ///< CxTest's container
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Test/CxTestManager.cpp>
#endif


// TODO: CxTestManager - not enough RAM
// TODO: CxTestManager - not enough HDD
// TODO: CxTestManager - busy CPU
// TODO: CxTestManager - every macros wrapped by try-catch
