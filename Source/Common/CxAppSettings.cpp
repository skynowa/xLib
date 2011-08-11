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
*    public, static
*
*****************************************************************************/

tString     CxAppSettings::m_sAppTitle;
tString     CxAppSettings::m_sAppDir;
tString     CxAppSettings::m_sDbDir;
tString     CxAppSettings::m_sDbBackupDir;
tString     CxAppSettings::m_sDbFilePath;
tString     CxAppSettings::m_sPass;
tString     CxAppSettings::m_sPassDefault;

const UCHAR CxAppSettings::m_ucDbEmpty[] = {
    #include "DbEmpty.db.zip.txt"
};
size_t      CxAppSettings::m_uiDbEmptySize = xARRAY_SIZE(CxAppSettings::m_ucDbEmpty);


/****************************************************************************
*    public
*
*****************************************************************************/


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxAppSettings
CxAppSettings::CxAppSettings() {

}
//---------------------------------------------------------------------------
//DONE: ~CxAppSettings
/*virtual*/
CxAppSettings::~CxAppSettings() {

}
//---------------------------------------------------------------------------
