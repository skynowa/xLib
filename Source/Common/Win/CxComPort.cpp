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
    const std::tstring &sPortNum
) :
    _m_bRes    (false),
    _m_sPortNum(sPortNum)
{
    /*DEBUG*/xASSERT_DO(false == _m_hComPort.bIsValid(), return);
}
//---------------------------------------------------------------------------
//TODO: ~CxCOMPort (����������)
CxCOMPort::~CxCOMPort() {
    /*DEBUG*/

    bClose();
}
//--------------------------------------------------------------------------
//TODO: bOpen (��������)
bool
CxCOMPort::bOpen() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    HANDLE hComPort = ::CreateFile(_m_sPortNum.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    /*DEBUG*/xASSERT_RET(INVALID_HANDLE_VALUE != hComPort, false);

    hComPort = _m_hComPort;

    return true;
}
//--------------------------------------------------------------------------
//TODO: bConfig (����������������)
bool
CxCOMPort::bConfig() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

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

    if (false == ::SetCommTimeouts(_m_hComPort, &timeouts))    {
        //
    }

    bClearData();

    ::SetCommMask(_m_hComPort, EV_DSR);

    ULONG lpEvtMask = 0;
    ::WaitCommEvent(_m_hComPort, &lpEvtMask, NULL);
    //CTest->OnRead();

    return false;
}
//--------------------------------------------------------------------------
//TODO: bClearData (����� ������)
bool
CxCOMPort::bClearData() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    ::PurgeComm(_m_hComPort, PURGE_RXCLEAR | PURGE_TXCLEAR); ////PurgeComm(_m_hComPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

    ULONG ulErrors;
    ::ClearCommError(_m_hComPort, &ulErrors, 0);

    return true;
}
//--------------------------------------------------------------------------
//TODO: bReadData (������ ������)
std::tstring
CxCOMPort::bReadData(
    LPTSTR pszBuff,
    ULONG  dwNumOfBytesToRead
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    CxCurrentThread::bSleep(5UL);

    DWORD dwNumOfBytesRead = 0;
    BOOL  bRes             = ::ReadFile(_m_hComPort, pszBuff, dwNumOfBytesToRead/*cuiSendStrLen*/, &dwNumOfBytesRead, NULL);
    if (FALSE == bRes) {
        return std::tstring();
    }
    if (dwNumOfBytesRead != dwNumOfBytesToRead) {
        return std::tstring();
    }

    return std::tstring(pszBuff, dwNumOfBytesRead);
}
//--------------------------------------------------------------------------
//TODO: iReadDataWaiting ()
int
CxCOMPort::iReadDataWaiting() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    return 0;
}
//--------------------------------------------------------------------------
//TODO: bWriteData (������ ������)
bool
CxCOMPort::bWriteData(
    LPCTSTR pcszBuff,
    DWORD   dwNumOfBytesToWrite
)
{
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    ULONG dwNumOfBytesWritten = 0;
    if (false == ::WriteFile(_m_hComPort, pcszBuff, dwNumOfBytesToWrite, &dwNumOfBytesWritten, NULL)) {
        return false;
    }

    if (dwNumOfBytesWritten != dwNumOfBytesToWrite) {
        return false;
    }

    if (false == ::FlushFileBuffers(_m_hComPort)) {
        return false;
    }

    return true;


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
            if (GetOverlappedResult(_m_hComPort, &osWrite, &dwWritten, true) == false) {
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
bool
CxCOMPort::bClose() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    _m_bRes = _m_hComPort.bClose();
    /*DEBUG*/xASSERT_RET(false != _m_bRes, false);

    return true;
}
//--------------------------------------------------------------------------
//TODO: ulInputBuffTest ()
ULONG
CxCOMPort::ulInputBuffTest() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    ULONG    dwErrors;
    _COMSTAT csStat;

    if (false == ::ClearCommError(_m_hComPort, &dwErrors, &csStat)) {
        return false;
    }

    return csStat.cbInQue;
}
//-------------------------------------------------------------------------
//TODO: bClearCLRDTR (����������� ������� DTR)
bool
CxCOMPort::bClearCLRDTR() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    return !!::EscapeCommFunction(_m_hComPort, CLRDTR);
}
//-------------------------------------------------------------------------
//TODO: bClearCLRRTS (����������� ������ RTS)
bool
CxCOMPort::bClearCLRRTS() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    return !!::EscapeCommFunction(_m_hComPort, CLRRTS);
}
//-------------------------------------------------------------------------
//TODO: bSetSETDTR (��������� ������� DTR)
bool
CxCOMPort::bSetSETDTR() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    return !!::EscapeCommFunction(_m_hComPort, SETDTR);
}
//-------------------------------------------------------------------------
//TODO: bSetSETRTS (��������� ������� RTS)
bool
CxCOMPort::bSetSETRTS() {
    /*DEBUG*/xASSERT_RET(false != _m_hComPort.bIsValid(), false);

    return !!::EscapeCommFunction(_m_hComPort, SETRTS);
}
//-------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
