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
                     CxCOMPort       (const std::string_t &sPortNum/* = xT("COM1")*/);
        virtual     ~CxCOMPort       ();

        BOOL         bOpen           ();
        BOOL         bConfig         ();
        BOOL         bClearData      ();
        std::string_t bReadData       (LPTSTR pszBuff, ULONG ulNumOfBytesToRead);
        int          iReadDataWaiting();
        BOOL         bWriteData      (LPCTSTR pcszBuff, ULONG ulNumOfBytesToWrite);
        BOOL         bClose          ();

        ULONG        ulInputBuffTest ();
        BOOL         bClearCLRDTR    ();
        BOOL         bClearCLRRTS    ();
        BOOL         bSetSETDTR      ();
        BOOL         bSetSETRTS      ();

    private:
        BOOL         _m_bRes;
        CxFileHandle _m_hComPort;
        std::string_t _m_sPortNum;

        COMMTIMEOUTS CommTimeOuts;
        DCB          dcb;
        COMSTAT      ComState;
        OVERLAPPED   Overlap;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
