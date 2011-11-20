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
                     CxCOMPort       (const std::tstring &sPortNum/* = xT("COM1")*/);
        virtual     ~CxCOMPort       ();

        bool         bOpen           ();
        bool         bConfig         ();
        bool         bClearData      ();
        std::tstring bReadData       (LPTSTR pszBuff, ULONG ulNumOfBytesToRead);
        int          iReadDataWaiting();
        bool         bWriteData      (LPCTSTR pcszBuff, ULONG ulNumOfBytesToWrite);
        bool         bClose          ();

        ULONG        ulInputBuffTest ();
        bool         bClearCLRDTR    ();
        bool         bClearCLRRTS    ();
        bool         bSetSETDTR      ();
        bool         bSetSETRTS      ();

    private:
        bool         _m_bRes;
        CxFileHandle _m_hComPort;
        std::tstring _m_sPortNum;

        COMMTIMEOUTS CommTimeOuts;
        DCB          dcb;
        COMSTAT      ComState;
        OVERLAPPED   Overlap;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
