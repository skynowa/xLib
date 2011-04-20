/****************************************************************************
* Class name:  CxCOMPort
* Description: COM port
* File name:   CxCOMPort.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.04.2010 9:29:26
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxComPortH
#define xLib_Common_Win_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandle.h>
//---------------------------------------------------------------------------
class CxCOMPort : public CxNonCopyable {
    public:
                     CxCOMPort       (const tString &sPortNum/* = xT("COM1")*/);
        virtual     ~CxCOMPort       ();
        
        BOOL         bOpen           ();
        BOOL         bConfig         ();
        BOOL         bClearData      ();
        tString      bReadData       (LPTSTR pszBuff, ULONG ulNumOfBytesToRead);
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
        CxHandle     _m_hComPort;  //INVALID_HANDLE_VALUE
        tString      _m_sPortNum;

        COMMTIMEOUTS CommTimeOuts;
        DCB          dcb;
        COMSTAT      ComState;              
        OVERLAPPED   Overlap;
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_Win_CxComPortH
