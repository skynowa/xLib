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
    explicit    CxTestManager(cbool_t &cbIsUseTracing);
        ///< constructor
    virtual    ~CxTestManager();
        ///< destructor

    void_t      add(CxTest *pvtTest);
        ///< add CxTest
    void_t      run(culonglong_t &cullAllLoops, culonglong_t &cullUnitLoops,
                    culonglong_t &cullCaseLoops);
        ///< run all tests

private:
    typedef std::vector<CxTest *> container_t;

    cbool_t     _m_cbIsUseTracing;   ///< is use tracing
    container_t _m_ctnTests;         ///< CxTest's container
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------

// TODO: CxTestManager - not enough RAM
// TODO: CxTestManager - not enough HDD
// TODO: CxTestManager - busy CPU
// TODO: CxTestManager - every macros wrapped by try-catch
