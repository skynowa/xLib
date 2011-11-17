/**
 * \file  CxComPort.cpp
 * \brief COM port
 */


#include <xLib/Common/Win/CxComPort.h>

#include <xLib/Sync/CxCurrentThread.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxCOMPort (�����������)
CxCOMPort::CxCOMPort(
    const std::string_t &sPortNum
) :
    _m_bRes    (FALSE),
    _m_sPortNum(sPortNum)
{
    /*DEBUG*/xASSERT_DO(FALSE == _m_hComPort.bIsValid(), return);
}
//---------------------------------------------------------------------------
//TODO: ~CxCOMPort (����������)
CxCOMPort::~CxCOMPort() {
    /*DEBUG*/

    bClose();
}
//--------------------------------------------------------------------------
//TODO: bOpen (��������)
BOOL
CxCOMPort::bOpen() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    HANDLE hComPort = ::CreateFile(_m_sPortNum.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hComPort, FALSE);

    hComPort = _m_hComPort;

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: bConfig (����������������)
BOOL
CxCOMPort::bConfig() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    DCB dcb;
    dcb.fOutxCtsFlow = false;                  //Disable CTS monitoring
    dcb.fOutxDsrFlow = false;                   //Disable DSR monitoring
    dcb.fDtrControl  = DTR_CONTROL_DISABLE;    //Disable DTR monitoring
    dcb.fOutX        = false;                  //Disable XON/XOFF for transmission
    dcb.fInX         = false;                  //Disable XON/XOFF for receiving
    dcb.fRtsControl  = RTS_CONTROL_DISABLE;    //Disable RTS (Ready To Send)

    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout         = 20;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.ReadTotalTimeoutConstant    = 100;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant   = 100;

    if (FALSE == ::SetCommTimeouts(_m_hComPort, &timeouts))    {
        //
    }

    bClearData();

    ::SetCommMask(_m_hComPort, EV_DSR);

    ULONG lpEvtMask = 0;
    ::WaitCommEvent(_m_hComPort, &lpEvtMask, NULL);
    //CTest->OnRead();

    return FALSE;
}
//--------------------------------------------------------------------------
//TODO: bClearData (����� ������)
BOOL
CxCOMPort::bClearData() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    ::PurgeComm(_m_hComPort, PURGE_RXCLEAR | PURGE_TXCLEAR); ////PurgeComm(_m_hComPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

    ULONG ulErrors;
    ::ClearCommError(_m_hComPort, &ulErrors, 0);

    return true;
}
//--------------------------------------------------------------------------
//TODO: bReadData (������ ������)
std::string_t
CxCOMPort::bReadData(
    LPTSTR pszBuff,
    ULONG  dwNumOfBytesToRead
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    CxCurrentThread::bSleep(5UL);

    DWORD dwNumOfBytesRead = 0;
    BOOL  bRes             = ::ReadFile(_m_hComPort, pszBuff, dwNumOfBytesToRead/*cuiSendStrLen*/, &dwNumOfBytesRead, NULL);
    if (FALSE == bRes) {
        return std::string_t();
    }
    if (dwNumOfBytesRead != dwNumOfBytesToRead) {
        return std::string_t();
    }

    return std::string_t(pszBuff, dwNumOfBytesRead);
}
//--------------------------------------------------------------------------
//TODO: iReadDataWaiting ()
int
CxCOMPort::iReadDataWaiting() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    return 0;
}
//--------------------------------------------------------------------------
//TODO: bWriteData (������ ������)
BOOL
CxCOMPort::bWriteData(
    LPCTSTR pcszBuff,
    DWORD   dwNumOfBytesToWrite
)
{
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    ULONG dwNumOfBytesWritten = 0;
    if (FALSE == ::WriteFile(_m_hComPort, pcszBuff, dwNumOfBytesToWrite, &dwNumOfBytesWritten, NULL)) {
        return FALSE;
    }

    if (dwNumOfBytesWritten != dwNumOfBytesToWrite) {
        return FALSE;
    }

    if (FALSE == ::FlushFileBuffers(_m_hComPort)) {
        return FALSE;
    }

    return TRUE;


#if xTODO
    OVERLAPPED osWrite   = {0};
    DWORD      dwWritten = 0;
    bool       bRes      = false;

    //Issue write
    if (!WriteFile(_m_hComPort, lpBuf, dwToWrite, &dwWritten, NULL)) {
        if (GetLastError() != ERROR_IO_PENDING) {  //WriteFile failed, but it isn't delayed. Report error and abort.
            bRes = false;
        } else {
            //Write is pending
            if (GetOverlappedResult(_m_hComPort, &osWrite, &dwWritten, TRUE) == false) {
                bRes = false;
            } else {
                //Write operation completed successfully.
                bRes = true;
            }
        }
    } else {
        //WriteFile completed immediately.
        bRes = true;
    }

    return bRes;
#endif
}
//--------------------------------------------------------------------------
//TODO: bClose (��������)
BOOL
CxCOMPort::bClose() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    _m_bRes = _m_hComPort.bClose();
    /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    return TRUE;
}
//--------------------------------------------------------------------------
//TODO: ulInputBuffTest ()
ULONG
CxCOMPort::ulInputBuffTest() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    ULONG    dwErrors;
    _COMSTAT csStat;

    if (FALSE == ::ClearCommError(_m_hComPort, &dwErrors, &csStat)) {
        return FALSE;
    }

    return csStat.cbInQue;
}
//-------------------------------------------------------------------------
//TODO: bClearCLRDTR (����������� ������� DTR)
BOOL
CxCOMPort::bClearCLRDTR() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    return ::EscapeCommFunction(_m_hComPort, CLRDTR);
}
//-------------------------------------------------------------------------
//TODO: bClearCLRRTS (����������� ������ RTS)
BOOL
CxCOMPort::bClearCLRRTS() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    return ::EscapeCommFunction(_m_hComPort, CLRRTS);
}
//-------------------------------------------------------------------------
//TODO: bSetSETDTR (��������� ������� DTR)
BOOL
CxCOMPort::bSetSETDTR() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    return ::EscapeCommFunction(_m_hComPort, SETDTR);
}
//-------------------------------------------------------------------------
//TODO: bSetSETRTS (��������� ������� RTS)
BOOL
CxCOMPort::bSetSETRTS() {
    /*DEBUG*/xASSERT_RET(FALSE != _m_hComPort.bIsValid(), FALSE);

    return ::EscapeCommFunction(_m_hComPort, SETRTS);
}
//-------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
