/**
 * \file  CxPath.h
 * \brief file system path
 */


#ifndef xLib_Filesystem_CxPathH
#define xLib_Filesystem_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxPath :
    public CxNonCopyable
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

        static std::string_t sGetExe         ();
            ///< get full path to exe
        static std::string_t sGetExeDir      ();
            ///< get dir path to exe
        static std::string_t sGetDll         ();
            ///< get full path to dll

    #if defined(xOS_ENV_WIN)
        static std::string_t sGetDrive       (const std::string_t &csFilePath);
            ///< get drive
    #endif
        static std::string_t sGetDir         (const std::string_t &csFilePath);
            ///< get dir path, without a trailing backslash '\'
        static std::string_t sGetDirName     (const std::string_t &csFilePath);
            ///< get dir name
        static std::string_t sGetFullName    (const std::string_t &csFilePath);
            ///< get name.extension
        static std::string_t sGetName        (const std::string_t &csFilePath);
            ///< get name without extension
        static std::string_t sGetExt         (const std::string_t &csFilePath);
            ///< get extension
        static std::string_t sGetStandartExt (const EStandartExt cseFileExt);
            ///< get standart extension

    #if defined(xOS_ENV_WIN)
        static std::string_t sSetDrive       (const std::string_t &csFilePath, const std::string_t &csDrivePath);
            ///< set drive
    #endif
        static std::string_t sSetDir         (const std::string_t &csFilePath, const std::string_t &csDirPath);
            ///< set dir
        static std::string_t sSetFullName    (const std::string_t &csFilePath, const std::string_t &csFullName);
            ///< set full name
        static std::string_t sSetName        (const std::string_t &csFilePath, const std::string_t &csName);
            ///< set name
        static std::string_t sSetExt         (const std::string_t &csFilePath, const std::string_t &csExt);
            ///< set extension

        static std::string_t sRemoveExt      (const std::string_t &csFilePath);
            ///< remove extention
        static std::string_t sRemoveExtIf    (const std::string_t &csFilePath, const std::string_t &csExt);
            ///< remove extension if it equal some string

        //normalize
        static BOOL         bIsValid        (const std::string_t &csFilePath);
            ///< path validation
        static BOOL         bIsNameValid    (const std::string_t &csFilePath);
            ///< name validation
        static BOOL         bIsAbsolute     (const std::string_t &csFilePath);
            ///< is absolute

        static std::string_t sToWin          (const std::string_t &csFilePath, const BOOL cbIsSlashAtEnd);
            ///< convert slashes to Windows style
        static std::string_t sToNix          (const std::string_t &csFilePath, const BOOL cbIsSlashAtEnd);
            ///< convert slashes to Nix style
        static std::string_t sToCurrentOs    (const std::string_t &csFilePath, const BOOL cbIsSlashAtEnd);
            ///< convert slashes to current OS style
        static std::string_t sGetAbsolute    (const std::string_t &csFilePath);
            ///< get absolute path

        static std::string_t sMinimizeName   (const std::string_t &csFileName, const size_t cuiMaxSize);
            ///< minimize name
        static std::string_t sMinimize       (const std::string_t &csFilePath, const size_t cuiMaxSize);
            ///< minimize path
        static std::string_t sSetValidName   (const std::string_t &csFileName);
            ///< set name as valid

        static std::string_t sSlashAppend    (const std::string_t &csDirPath);
            ///< append slash
        static std::string_t sSlashRemove    (const std::string_t &csDirPath);
            ///< remove slash

        static size_t       uiGetMaxSize    ();
            ///< get max path length in symbols
        static size_t       uiGetNameMaxSize();
            ///< get max name length in symbols

    private:
                            CxPath          ();
            ///< constructor
        virtual            ~CxPath          ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxPathH


/*
_MAX_DIR
_MAX_DRIVE
_MAX_EXT
_MAX_FNAME
_MAX_PATH
*/



//static std::string_t sGetRelativePath     (const std::string_t &csFilePath);

/*ExpandUNCFileName*/
/*ExtractShortPathName*/
/*ProcessPath*/

/*
 String
   FileUtilities::GetShortPath(const String &sInPath)
   {
      char_t szModuleShort[_MAX_PATH];
      GetShortPathName(sInPath, szModuleShort, _MAX_PATH );

      return szModuleShort;
   }

   String
   FileUtilities::GetLongPath(const String &sInPath)
   {
      char_t szLong[_MAX_PATH];
      GetLongPathName(sInPath, szLong, _MAX_PATH );

      return szLong;
   }
*/
