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

                     CWorkThread(const BOOL cbAutoDelete);
        virtual     ~CWorkThread();

    protected:
        virtual UINT uiOnRun    (void *pData);
};
//---------------------------------------------------------------------------
class CxTest_CxThread :
    public CxTest
{
    public:
                     CxTest_CxThread();
        virtual     ~CxTest_CxThread();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxThreadH
