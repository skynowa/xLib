/**
 * \file   CxTest_CxThread.h
 * \brief
 */


#ifndef CxTest_CxThreadH
#define CxTest_CxThreadH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Sync/CxThread.h>
#include <xLib/Sync/CxCurrentThread.h>
//---------------------------------------------------------------------------
class CWorkThread :
    public CxThread
    ///< tests thread
{
    public:
        size_t       m_uiIndex;

                     CWorkThread(const bool cbAutoDelete);
        virtual     ~CWorkThread();

    protected:
        virtual uint_t uiOnRun    (void *pData);
};
//---------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
    public:
                     CxTest_CxThread();
        virtual     ~CxTest_CxThread();

        virtual bool bUnit(const ulonglong_t cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadH
