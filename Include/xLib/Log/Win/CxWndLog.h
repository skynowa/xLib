/****************************************************************************
* Class name:  CxWndLog
* Description: logging to window
* File name:   CxWndLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:44:10
*
*****************************************************************************/


#ifndef xLib_Log_CxWndLogH
#define xLib_Log_CxWndLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <xLib/Sync/CxCriticalSection.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxWndLog :
    public CxNonCopyable
{
    public:
        //window classes
        enum EWindowClass {
            wcListBox
        };

                                 CxWndLog(EWindowClass wcWC);
        virtual                 ~CxWndLog();

           BOOL                     bWrite  (HWND hWnd, LPCTSTR pcszFormat, ...);

       private:
           EWindowClass             _m_eWC;
           static CxCriticalSection _ms_csListBox;  //Mutex
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif
