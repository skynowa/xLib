/****************************************************************************
* Class name:  CxAppSettings
* Description: application settings
* File name:   CxAppSettings.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     25.11.2010 9:23:47
*
*****************************************************************************/


#include <xLib/Common/CxAppSettings.h>


/****************************************************************************
*	public, static                                                         
*                                                                            
*****************************************************************************/

tString 	CxAppSettings::m_sAppTitle    = xT("");
tString 	CxAppSettings::m_sAppDir      = xT("");
tString 	CxAppSettings::m_sDbDir       = xT("");
tString 	CxAppSettings::m_sDbBackupDir = xT("");
tString 	CxAppSettings::m_sDbFilePath  = xT("");
tString 	CxAppSettings::m_sPass        = xT("");
tString 	CxAppSettings::m_sPassDefault = xT("");

const UCHAR CxAppSettings::m_ucDbEmpty[]  = {		
	#include "DbEmpty.db.zip.txt"
};
ULONG CxAppSettings::m_ulDbEmptySize      = xARRAY_SIZE(CxAppSettings::m_ucDbEmpty);


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------







/****************************************************************************
*    private                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxAppSettings (comment)
CxAppSettings::CxAppSettings() {

}
//---------------------------------------------------------------------------
//TODO: - ~CxAppSettings (comment)
/*virtual*/
CxAppSettings::~CxAppSettings() {

}
//---------------------------------------------------------------------------
