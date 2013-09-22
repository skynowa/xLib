/**
 * \file   CxTest_CxThreadPool.h
 * \brief  test CxThreadPool
 */


#pragma once

#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Sync/CxThreadPool.h>
//------------------------------------------------------------------------------
class CxTest_CxThreadPool :
    public CxTest
{
public:
                   CxTest_CxThreadPool();
        ///< constructor
    virtual       ~CxTest_CxThreadPool();
        ///< destructor

    virtual void_t unit(culonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
class CPoolThread :
    public CxThread
{
public:
    size_t         m_uiIndex;

                   CPoolThread(cbool_t &cbAutoDelete);
    virtual       ~CPoolThread();

protected:
    virtual uint_t uiOnRun(void_t *pData);
};
//------------------------------------------------------------------------------
