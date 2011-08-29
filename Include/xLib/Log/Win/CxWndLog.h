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
        enum EWindowClass
        	/// window classes
        {
            wcListBox
        };

        explicit                    CxWndLog(const EWindowClass cwcWC);
            ///< constructor
        virtual                    ~CxWndLog();
        	///< destructor

        BOOL                        bWrite  (const HWND chWnd, LPCTSTR pcszFormat, ...);
        	///< write

       private:
           EWindowClass             _m_eWC;			///< window class
           static CxCriticalSection _ms_csListBox;	///< critical section
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif
