/**
 * \file  CxComPort.h
 * \brief COM port
 */


#ifndef xLib_Common_Win_CxComPortH
#define xLib_Common_Win_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxCOMPort :
    public CxNonCopyable
    /// COM port
{
    public:
                     CxCOMPort       (const std::tstring &sPortNum/* = xT("COM1")*/);
        virtual     ~CxCOMPort       ();

        BOOL         bOpen           ();
        BOOL         bConfig         ();
        BOOL         bClearData      ();
        std::tstring bReadData       (LPTSTR pszBuff, ULONG ulNumOfBytesToRead);
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
        std::tstring _m_sPortNum;

        COMMTIMEOUTS CommTimeOuts;
        DCB          dcb;
        COMSTAT      ComState;
        OVERLAPPED   Overlap;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
