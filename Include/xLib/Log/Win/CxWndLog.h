/**
 * \file  CxWndLog.h
 * \brief logging to window
 */


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
    /// logging to window
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
