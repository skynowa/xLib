/****************************************************************************
* Class name:  CxFileLog
* Description: logging to file
* File name:   CxFileLog.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.06.2009 17:40:37
*
*****************************************************************************/


#ifndef xLib_Log_CxFileLogH
#define xLib_Log_CxFileLogH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxCriticalSection.h>
//---------------------------------------------------------------------------
class CxFileLog : public CxNonCopyable {
	public:
		enum ELogSizes {
			lsDefaultSize    = 20,
			lsDefaultMaxSize = 200,
			lsLimitSize      = 500
		};	
			
						  CxFileLog    ();
						  CxFileLog    (const tString &csFilePath, ULONG ulMaxFileSizeMb);
		virtual     	 ~CxFileLog    ();

		BOOL              bWrite       (LPCTSTR pcszFormat, ...); 
		BOOL              bOpen        ();
		BOOL              bClear       ();
		BOOL              bDelete      ();
	   
	private:	
		tString           _m_sLogPath;
		ULONG             _m_ulMaxFileSizeMb;
		////CxCriticalSection _m_csFile;    //TODO: Mutex
		
		BOOL              _bDeleteIfFull();
};
//---------------------------------------------------------------------------
#endif	//xLib_Log_CxFileLogH
