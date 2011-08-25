/**
 * \file  CxAppSettings.cpp
 * \brief application settings
 */


#include <xLib/Common/CxAppSettings.h>


/****************************************************************************
*    public, static
*
*****************************************************************************/

std::tstring     CxAppSettings::m_sAppTitle;
std::tstring     CxAppSettings::m_sAppDir;
std::tstring     CxAppSettings::m_sDbDir;
std::tstring     CxAppSettings::m_sDbBackupDir;
std::tstring     CxAppSettings::m_sDbFilePath;
std::tstring     CxAppSettings::m_sPass;
std::tstring     CxAppSettings::m_sPassDefault;

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
