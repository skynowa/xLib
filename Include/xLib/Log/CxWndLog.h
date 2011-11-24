/**
 * \file  CxWndLog.h
 * \brief logging to window
 */


#ifndef xLib_Log_CxWndLogH
#define xLib_Log_CxWndLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxWndLog :
    public CxNonCopyable
    /// logging to window
{
    public:
    #if xOS_ENV_WIN
        typedef HWND    TxHandle; ///< window handle
    #elif xOS_ENV_UNIX
        typedef int     TxHandle; ///< window handle
    #endif


        enum EWindowClass
            /// window classes
        {
            wcListBox
        };

        explicit                    CxWndLog(const EWindowClass cwcWC);
            ///< constructor
        virtual                    ~CxWndLog();
            ///< destructor

        bool                        bWrite  (const TxHandle chWnd, const tchar_t *pcszFormat, ...);
            ///< write

       private:
           EWindowClass             _m_eWC;         ///< window class
           static CxCriticalSection _ms_csListBox;  ///< critical section
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif
