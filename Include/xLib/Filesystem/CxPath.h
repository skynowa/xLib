/**
 * \file  CxPath.h
 * \brief file system path
 */


#ifndef xLib_Filesystem_CxPathH
#define xLib_Filesystem_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxPath :
    private CxNonCopyable
    /// file system path
{
    public:
        enum EStandartExt
            /// standart extension
        {
            seExe,  ///< execute module
            seDll,  ///< dynamically linked shared library
            seLib,  ///< static library
            seObj   ///< object file
        };

        static std::tstring_t sGetExe         ();
            ///< get full path to exe
        static std::tstring_t sGetExeDir      ();
            ///< get dir path to exe
        static std::tstring_t sGetDll         ();
            ///< get full path to dll

    #if xOS_ENV_WIN
        static std::tstring_t sGetDrive       (const std::tstring_t &csFilePath);
            ///< get drive
    #endif
        static std::tstring_t sGetDir         (const std::tstring_t &csFilePath);
            ///< get dir path, without a trailing backslash '\'
        static std::tstring_t sGetDirName     (const std::tstring_t &csFilePath);
            ///< get dir name
        static std::tstring_t sGetFullName    (const std::tstring_t &csFilePath);
            ///< get name.extension
        static std::tstring_t sGetName        (const std::tstring_t &csFilePath);
            ///< get name without extension
        static std::tstring_t sGetExt         (const std::tstring_t &csFilePath);
            ///< get extension
        static std::tstring_t sGetStandartExt (const EStandartExt cseFileExt);
            ///< get standart extension

    #if xOS_ENV_WIN
        static std::tstring_t sSetDrive       (const std::tstring_t &csFilePath, const std::tstring_t &csDrivePath);
            ///< set drive
    #endif
        static std::tstring_t sSetDir         (const std::tstring_t &csFilePath, const std::tstring_t &csDirPath);
            ///< set dir
        static std::tstring_t sSetFullName    (const std::tstring_t &csFilePath, const std::tstring_t &csFullName);
            ///< set full name
        static std::tstring_t sSetName        (const std::tstring_t &csFilePath, const std::tstring_t &csName);
            ///< set name
        static std::tstring_t sSetExt         (const std::tstring_t &csFilePath, const std::tstring_t &csExt);
            ///< set extension

        static std::tstring_t sRemoveExt      (const std::tstring_t &csFilePath);
            ///< remove extention
        static std::tstring_t sRemoveExtIf    (const std::tstring_t &csFilePath, const std::tstring_t &csExt);
            ///< remove extension if it equal some string

        //normalize
        static bool           bIsValid        (const std::tstring_t &csFilePath);
            ///< path validation
        static bool           bIsNameValid    (const std::tstring_t &csFilePath);
            ///< name validation
        static bool           bIsAbsolute     (const std::tstring_t &csFilePath);
            ///< is absolute

        static std::tstring_t sToWin          (const std::tstring_t &csFilePath, const bool cbIsSlashAtEnd);
            ///< convert slashes to Windows style
        static std::tstring_t sToNix          (const std::tstring_t &csFilePath, const bool cbIsSlashAtEnd);
            ///< convert slashes to Nix style
        static std::tstring_t sToCurrentOs    (const std::tstring_t &csFilePath, const bool cbIsSlashAtEnd);
            ///< convert slashes to current OS style
        static std::tstring_t sGetAbsolute    (const std::tstring_t &csFilePath);
            ///< get absolute path

        static std::tstring_t sMinimizeName   (const std::tstring_t &csFileName, const size_t cuiMaxSize);
            ///< minimize name
        static std::tstring_t sMinimize       (const std::tstring_t &csFilePath, const size_t cuiMaxSize);
            ///< minimize path
        static std::tstring_t sSetValidName   (const std::tstring_t &csFileName);
            ///< set name as valid

        static std::tstring_t sSlashAppend    (const std::tstring_t &csDirPath);
            ///< append slash
        static std::tstring_t sSlashRemove    (const std::tstring_t &csDirPath);
            ///< remove slash

        static size_t         uiGetMaxSize    ();
            ///< get max path length in symbols
        static size_t         uiGetNameMaxSize();
            ///< get max name length in symbols

    #if xOS_ENV_UNIX || 1
        static std::tstring_t sGetProcLine    (const std::tstring_t  &csProcPath, const std::tstring_t &csTargetStr);
            ///< get UNIX proc file content
    #endif

    private:
                              CxPath          ();
            ///< constructor
        virtual              ~CxPath          ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxPathH


/*
_MAX_DIR
_MAX_DRIVE
_MAX_EXT
_MAX_FNAME
_MAX_PATH
*/



//static std::tstring_t sGetRelativePath     (const std::tstring_t &csFilePath);

/*ExpandUNCFileName*/
/*ExtractShortPathName*/
/*ProcessPath*/

/*
 String
   FileUtilities::GetShortPath(const String &sInPath)
   {
      tchar_t szModuleShort[_MAX_PATH];
      GetShortPathName(sInPath, szModuleShort, _MAX_PATH );

      return szModuleShort;
   }

   String
   FileUtilities::GetLongPath(const String &sInPath)
   {
      tchar_t szLong[_MAX_PATH];
      GetLongPathName(sInPath, szLong, _MAX_PATH );

      return szLong;
   }
*/
