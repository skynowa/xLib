/**
 * \file  CxAppSettings.h
 * \brief application settings
 */


#ifndef xLib_Common_CxAppSettingsH
#define xLib_Common_CxAppSettingsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxAppSettings :
    public CxNonCopyable
    /// application settings
{
    public:
        static std::tstring     m_sAppTitle;
        static std::tstring     m_sAppDir;
        static std::tstring     m_sDbDir;
        static std::tstring     m_sDbBackupDir;
        static std::tstring     m_sDbFilePath;

        static const UCHAR m_ucDbEmpty[];
        static size_t      m_uiDbEmptySize;
        static std::tstring     m_sPass;
        static std::tstring     m_sPassDefault;

    private:
                           CxAppSettings();
        virtual           ~CxAppSettings();
};
//---------------------------------------------------------------------------
#endif //xLib_Common_CxAppSettingsH
