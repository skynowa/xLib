/**
 * \file   CxTest_CxThreadPool.h
 * \brief  test CxThreadPool
 */


#ifndef CxTest_CxThreadPoolH
#define CxTest_CxThreadPoolH
//------------------------------------------------------------------------------
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
    virtual      ~CxTest_CxThreadPool();
        ///< destructor

    virtual void unit(const ulonglong_t &cullCaseLoops);
        ///< unit test
};
//------------------------------------------------------------------------------
class CPoolThread :
    public CxThread
{
public:
    size_t         m_uiIndex;

                   CPoolThread(const bool &cbAutoDelete);
    virtual       ~CPoolThread();

protected:
    virtual uint_t uiOnRun    (void *pData);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxThreadPoolH
