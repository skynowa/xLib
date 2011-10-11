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
            seExe,	///< execute module
            seDll,	///< dynamically linked shared library
            seLib	///< static library
        };

        static std::tstring sGetExe         ();
        	///< get full path to exe
        static std::tstring sGetExeDir      ();
        	///< get dir path to exe
        static std::tstring sGetDll         ();
        	///< get full path to dll

    #if defined(xOS_ENV_WIN)
        static std::tstring sGetDrive       (const std::tstring &csFilePath);
        	///< get drive
    #endif
        static std::tstring sGetDir         (const std::tstring &csFilePath);
        	///< get dir path, without a trailing backslash '\'
        static std::tstring sGetDirName     (const std::tstring &csFilePath);
        	///< get dir name
        static std::tstring sGetFullName    (const std::tstring &csFilePath);
        	///< get name.extension
        static std::tstring sGetName        (const std::tstring &csFilePath);
        	///< get name without extension
        static std::tstring sGetExt         (const std::tstring &csFilePath);
        	///< get extension
        static std::tstring sGetStandartExt (const EStandartExt cseFileExt);
        	///< get standart extension

    #if defined(xOS_ENV_WIN)
        static std::tstring sSetDrive       (const std::tstring &csFilePath, const std::tstring &csDrivePath);
        	///< set drive
    #endif
        static std::tstring sSetDir         (const std::tstring &csFilePath, const std::tstring &csDirPath);
        	///< set dir
        static std::tstring sSetFullName    (const std::tstring &csFilePath, const std::tstring &csFullName);
        	///< set full name
        static std::tstring sSetName        (const std::tstring &csFilePath, const std::tstring &csName);
        	///< set name
        static std::tstring sSetExt         (const std::tstring &csFilePath, const std::tstring &csExt);
        	///< set extension

        static std::tstring sRemoveExt      (const std::tstring &csFilePath);
        	///< remove extention
        static std::tstring sRemoveExtIf    (const std::tstring &csFilePath, const std::tstring &csExt);
        	///< remove extension if it equal some string

        //normalize
        static BOOL         bIsValid        (const std::tstring &csFilePath);
        	///< path validation
        static BOOL         bIsNameValid    (const std::tstring &csFilePath);
        	///< name validation
        static BOOL         bIsAbsolute     (const std::tstring &csFilePath);
        	///< is absolute

        static std::tstring sToWin          (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);
        	///< convert slashes to Windows style
        static std::tstring sToNix          (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);
        	///< convert slashes to Nix style
        static std::tstring sToCurrentOs    (const std::tstring &csFilePath, const BOOL cbIsSlashAtEnd);
        	///< convert slashes to current OS style
        static std::tstring sGetAbsolute    (const std::tstring &csFilePath);
        	///< get absolute path

        static std::tstring sMinimizeName   (const std::tstring &csFileName, const size_t cuiMaxSize);
        	///< minimize name
        static std::tstring sMinimize       (const std::tstring &csFilePath, const size_t cuiMaxSize);
        	///< minimize path
        static std::tstring sSetValidName   (const std::tstring &csFileName);
        	///< set name as valid

        static std::tstring sSlashAppend    (const std::tstring &csDirPath);
        	///< append slash
        static std::tstring sSlashRemove    (const std::tstring &csDirPath);
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



//static std::tstring sGetRelativePath     (const std::tstring &csFilePath);

/*ExpandUNCFileName*/
/*ExtractShortPathName*/
/*ProcessPath*/

/*
 String
   FileUtilities::GetShortPath(const String &sInPath)
   {
      TCHAR szModuleShort[_MAX_PATH];
      GetShortPathName(sInPath, szModuleShort, _MAX_PATH );

      return szModuleShort;
   }

   String
   FileUtilities::GetLongPath(const String &sInPath)
   {
      TCHAR szLong[_MAX_PATH];
      GetLongPathName(sInPath, szLong, _MAX_PATH );

      return szLong;
   }
*/
