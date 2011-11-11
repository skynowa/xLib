/**
 * \file  CxAppSettings.h
 * \brief application settings
 */


#ifndef xLib_Common_CxAppSettingsH
#define xLib_Common_CxAppSettingsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAppSettings :
    public CxNonCopyable
    /// application settings
{
    public:
        static std::string_t m_sAppTitle;
        static std::string_t m_sAppDir;
        static std::string_t m_sDbDir;
        static std::string_t m_sDbBackupDir;
        static std::string_t m_sDbFilePath;

        static const UCHAR  m_ucDbEmpty[];
        static size_t       m_uiDbEmptySize;
        static std::string_t m_sPass;
        static std::string_t m_sPassDefault;

    private:
                            CxAppSettings();
        virtual            ~CxAppSettings();
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Common_CxAppSettingsH
