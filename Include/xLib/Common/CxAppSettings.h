/****************************************************************************
* Class name:  CxAppSettings
* Description: application settings
* File name:   CxAppSettings.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.11.2010 9:23:47
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_CxAppSettingsH
#define xLib_Common_CxAppSettingsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#ifdef __BORLANDC__
	#include <xVCL/xCommon.h>
#endif
//---------------------------------------------------------------------------
class CxAppSettings : public CxNonCopyable {
	private:
				           CxAppSettings();
		virtual           ~CxAppSettings();

	public:
		static tString     m_sAppTitle;
		static tString     m_sAppDir;
		static tString     m_sDbDir;
		static tString     m_sDbBackupDir;
		static tString     m_sDbFilePath;

		static const UCHAR m_ucDbEmpty[];
		static ULONG       m_ulDbEmptySize;
		static tString     m_sPass;
		static tString     m_sPassDefault;
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxAppSettingsH
