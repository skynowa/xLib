/****************************************************************************
* Class name:  CxFileLog
* Description: logging to file
* File name:   CxFileLog.cpp
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     01.06.2009 17:40:37
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Log/CxFileLog.h>

#include <xLib/Common/CxDateTime.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxStdioFile.h>
#include <xLib/Sync/CxProcess.h>
////#include <xLib/Sync/CxAutoCriticalSection.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + CxFileLog (constructor)
CxFileLog::CxFileLog() : 
	_m_sLogPath       (), 
	_m_ulMaxFileSizeMb(lsDefaultMaxSize)
////	_m_csFile         ()
{
	/*DEBUG*/xASSERT_DO(lsLimitSize > lsDefaultMaxSize, return);

	//�� ������ ���� (��� �����)
	_m_sLogPath = CxPath::sSetExt(CxPath::sGetExe(), xT("exe.log"));
}
//---------------------------------------------------------------------------
//TODO: + CxFileLog (constructor)
CxFileLog::CxFileLog(const tString &csFilePath, ULONG ulMaxFileSizeMb) : 
	_m_sLogPath       (), 
	_m_ulMaxFileSizeMb(ulMaxFileSizeMb)////,
    ////_m_csFile         ()
{
	/*DEBUG*/xASSERT_DO(false      == csFilePath.empty(), return);
	/*DEBUG*/xASSERT_DO(lsLimitSize > ulMaxFileSizeMb,    return);
	/*DEBUG*/xASSERT_DO(lsLimitSize > lsDefaultMaxSize,   return);

	//��� ����� - �� �������� "\"
	if (tString::npos == csFilePath.find(CxConst::xSLASH)) {
		//�� ������ ���� (��� �����)
		_m_sLogPath = CxPath::sGetDir(CxPath::sGetExe()) + CxConst::xSLASH + csFilePath/* + ".log"*/;
	} else {
		//������ ����
		_m_sLogPath = csFilePath;
	}
}
//---------------------------------------------------------------------------
//TODO: + ~CxFileLog (destructor)
CxFileLog::~CxFileLog() {

}
//---------------------------------------------------------------------------
//TODO: + bWrite (write)
BOOL
CxFileLog::bWrite(LPCTSTR pcszFormat, ...) {
	/*DEBUG*/xASSERT_RET(NULL != pcszFormat, FALSE);

	BOOL bRes = FALSE;

	bRes = _bDeleteIfFull();
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	//-------------------------------------
	//time
	tString sTime;
	sTime = CxDateTime::dtGetCurrent().sFormat(CxDateTime::ftTime);

	//-------------------------------------
	//comment
	tString sParam;
	va_list palArgs = NULL;

	va_start(palArgs, pcszFormat);
	sParam = CxString::sFormatV(pcszFormat, palArgs);
	va_end(palArgs);	

	//-------------------------------------
	//write to file
	/////*LOCK*/CxAutoCriticalSection SL(_m_csFile);

	CxStdioFile sfFile;

	bRes = sfFile.bOpen(_m_sLogPath, xT("a"));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	sfFile.iFprintf(xT("[%s] %s\n"), sTime.c_str(), sParam.c_str());

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bOpen (execute)
BOOL
CxFileLog::bOpen() {
	BOOL bRes = FALSE;

	bRes = CxProcess::bExec(_m_sLogPath, xT(""));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bClear (clear content)
BOOL
CxFileLog::bClear() {
	BOOL bRes = FALSE;

	/////*LOCK*/CxAutoCriticalSection SL(_m_csFile);

	CxStdioFile sfFile;
	
	bRes = sfFile.bOpen(_m_sLogPath, xT("w"));
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
	
	sfFile.iFprintf(xT(""));

	return TRUE;
}
//---------------------------------------------------------------------------
//TODO: + bDelete (delete)
BOOL
CxFileLog::bDelete() {
	BOOL bRes = FALSE;

	/////*LOCK*/CxAutoCriticalSection SL(_m_csFile);

	bRes = CxStdioFile::bDelete(_m_sLogPath);
	/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

	return TRUE;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: + _bDeleteIfFull (delete log, if it is full)
BOOL
CxFileLog::_bDeleteIfFull() {
	BOOL bRes = FALSE;

	/////*LOCK*/CxAutoCriticalSection SL(_m_csFile);

	bRes = CxStdioFile::bIsExists(_m_sLogPath);
	xCHECK_RET(FALSE == bRes, TRUE);

	LONG liSize = CxStdioFile::liGetSize(_m_sLogPath);

	//-------------------------------------
	//delete log, if it is full
	if (static_cast<ULONG>(liSize / 1000000) >= _m_ulMaxFileSizeMb) {
		bRes = CxStdioFile::bDelete(_m_sLogPath);
		/*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
