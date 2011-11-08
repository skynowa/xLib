/**
 * \file  CxAppSettings.cpp
 * \brief application settings
 */


#include <xLib/Common/CxAppSettings.h>


/****************************************************************************
*    public, static
*
*****************************************************************************/

std::string_t  CxAppSettings::m_sAppTitle;
std::string_t  CxAppSettings::m_sAppDir;
std::string_t  CxAppSettings::m_sDbDir;
std::string_t  CxAppSettings::m_sDbBackupDir;
std::string_t  CxAppSettings::m_sDbFilePath;
std::string_t  CxAppSettings::m_sPass;
std::string_t  CxAppSettings::m_sPassDefault;

const UCHAR   CxAppSettings::m_ucDbEmpty[] = {
    #include "DbEmpty.db.zip.txt"
};
size_t        CxAppSettings::m_uiDbEmptySize = xARRAY_SIZE(CxAppSettings::m_ucDbEmpty);


/****************************************************************************
*    public
*
*****************************************************************************/


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxAppSettings::CxAppSettings() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxAppSettings::~CxAppSettings() {

}
//---------------------------------------------------------------------------
