/***********************************************************************
*   ��������� ��������� � ini-����� (��� �����)
*
************************************************************************/


#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
void vSendCmdToDVD(const String &csDriveLetter, BOOL bOpenFlag) {
	//�������
	TCHAR *pszCdCmdSet       = _T("set");
	////TCHAR *pszCdCmdStatus    = _T("status");
	////TCHAR *pszCdCmdPlay      = _T("play");
	////TCHAR *pszCdCmdPause     = _T("pause");
	////TCHAR *pszCdCmdStop      = _T("stop");
	////TCHAR *pszCdCmdResume    = _T("resume");

	//����� ������
	TCHAR *pszCdCmdFlagOpen  = _T("door open");
	TCHAR *pszCdCmdFlagClose = _T("door closed");
	////TCHAR *pszCdCmdCurTrack  = _T("current track");
	////TCHAR *pszCdCmdCurMode   = _T("mode");
	////TCHAR *pszCdCmdFlagEmpty = _T("");

	//����� ����������
	TCHAR *pszCdFlagWait     = _T("wait");
	////TCHAR *pszCdFlagEmpty    = _T("");

	//�������� ������� � ��������� ����� CD-ROM'� [Set cdaudio door open wait]
	String sCmd;
	
	if (true == bOpenFlag) {
		sCmd.sprintf(_T("%s cdaudio!%s: %s %s"), pszCdCmdSet, csDriveLetter, pszCdCmdFlagOpen,  pszCdFlagWait);
	} else {
		sCmd.sprintf(_T("%s cdaudio!%s: %s %s"), pszCdCmdSet, csDriveLetter, pszCdCmdFlagClose, pszCdFlagWait);
    }                        

	::mciSendString(sCmd.c_str(), NULL, 0, INVALID_HANDLE_VALUE);
}
//---------------------------------------------------------------------------