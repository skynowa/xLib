/**
 * \file  CxComPort.h
 * \brief COM port
 */


#ifndef xLib_Common_Win_CxComPortH
#define xLib_Common_Win_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#if defined(xOS_ENV_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
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
        INT          iReadDataWaiting();
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
#elif defined(xOS_ENV_UNIX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
