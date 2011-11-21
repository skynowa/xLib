/**
 * \file  CxComPort.h
 * \brief COM port
 */


#ifndef xLib_Common_Win_CxComPortH
#define xLib_Common_Win_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#if xOS_ENV_WIN
    #include <xLib/Common/Win/CxHandleT.h>
#elif xOS_ENV_UNIX

#endif
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxCOMPort :
    public CxNonCopyable
    /// COM port
{
    public:
                     CxCOMPort       (const std::tstring_t &sPortNum/* = xT("COM1")*/);
        virtual     ~CxCOMPort       ();

        bool         bOpen           ();
        bool         bConfig         ();
        bool         bClearData      ();
        std::tstring_t bReadData       (LPTSTR pszBuff, ulong_t ulNumOfBytesToRead);
        int          iReadDataWaiting();
        bool         bWriteData      (LPCTSTR pcszBuff, ulong_t ulNumOfBytesToWrite);
        bool         bClose          ();

        ulong_t        ulInputBuffTest ();
        bool         bClearCLRDTR    ();
        bool         bClearCLRRTS    ();
        bool         bSetSETDTR      ();
        bool         bSetSETRTS      ();

    private:
        bool         _m_bRes;
        CxFileHandle _m_hComPort;
        std::tstring_t _m_sPortNum;

        COMMTIMEOUTS CommTimeOuts;
        DCB          dcb;
        COMSTAT      ComState;
        OVERLAPPED   Overlap;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
