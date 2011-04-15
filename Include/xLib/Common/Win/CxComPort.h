/****************************************************************************
* Class name:  CxCOMPort
* Description: COM port
* File name:   CxCOMPort.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     19.04.2010 9:29:26
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_Win_CxComPortH
#define xLib_Common_Win_CxComPortH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandleT.h>
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
		CxHandleT<INVALID_HANDLE_VALUE> _m_hComPort;
		tString      _m_sPortNum;

		COMMTIMEOUTS CommTimeOuts;
		DCB          dcb;
		COMSTAT      ComState;              
		OVERLAPPED   Overlap;
};
//---------------------------------------------------------------------------
#endif	//xLib_Common_Win_CxComPortH
