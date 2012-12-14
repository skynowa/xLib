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
        enum ExStandartExt
            /// standard extension
        {
            seExe,  ///< execute module
            seDll,  ///< dynamically linked shared library
            seLib,  ///< static library
            seObj,  ///< object file
            seShell ///< shell script file
        };

        explicit               CxPath          (const std::tstring_t &csFilePath);
            ///< constructor
        virtual               ~CxPath          ();
            ///< destructor
                             
        const std::tstring_t & sFilePath       () const;
            ///< file path

    #if xOS_ENV_WIN
        std::tstring_t         sDrive          () const;
            ///< get drive
    #endif
        std::tstring_t         sDir            () const;
            ///< get dir path, without a trailing backslash '\'
        std::tstring_t         sDirName        () const;
            ///< get dir name
        std::tstring_t         sFileName       () const;
            ///< get name.extension
        std::tstring_t         sFileBaseName   () const;
            ///< get name without extension
        std::tstring_t         sExt            () const;
            ///< get extension

    #if xOS_ENV_WIN
        std::tstring_t         sSetDrive       (const std::tstring_t &csDrivePath);
            ///< set drive
    #endif
        std::tstring_t         sSetDir         (const std::tstring_t &csDirPath);
            ///< set dir
        std::tstring_t         sSetFileName    (const std::tstring_t &csFullName);
            ///< set full name
        std::tstring_t         sSetFileBaseName(const std::tstring_t &csName);
            ///< set name
        std::tstring_t         sSetExt         (const std::tstring_t &csExt);
            ///< set extension

        std::tstring_t         sRemoveExt      ();
            ///< remove extension
        std::tstring_t         sRemoveExtIf    (const std::tstring_t &csExt);
            ///< remove extension if it equal some string


        bool                   bIsAbsolute     () const;
            ///< is absolute

        std::tstring_t         sToWin          (const bool &cbIsSlashAtEnd) const;
            ///< convert slashes to Windows style
        std::tstring_t         sToUnix         (const bool &cbIsSlashAtEnd) const;
            ///< convert slashes to Nix style
        std::tstring_t         sToNative       (const bool &cbIsSlashAtEnd) const;
            ///< convert slashes to native style
        std::tstring_t         sAbsolute       () const;
            ///< get absolute path
        std::tstring_t         sShort          (const size_t &cuiMaxSize) const;
            ///< get short path

        std::tstring_t         sSlashAppend    () const;
            ///< append slash
        std::tstring_t         sSlashRemove    () const;
            ///< remove slash

        // static
        static std::tstring_t  sExe            ();
            ///< get full path to exe
        static std::tstring_t  sExeDir         ();
            ///< get dir path to exe
        static std::tstring_t  sDll            ();
            ///< get full path to dll
        static std::tstring_t  sStandartExt    (const ExStandartExt &cseFileExt);
            ///< get standard extension

        static bool            bIsValid        (const std::tstring_t &csFilePath);
            ///< path validation
        static bool            bIsNameValid    (const std::tstring_t &csFileName);
            ///< name validation

        static std::tstring_t  sShortName      (const std::tstring_t &csFileName, const size_t &cuiMaxSize);
            ///< get short name
        static std::tstring_t  sSetNameValid   (const std::tstring_t &csFileName);
            ///< set name as valid

        static size_t          uiMaxSize       ();
            ///< get max path length in symbols
        static size_t          uiNameMaxSize   ();
            ///< get max name length in symbols

    #if xOS_ENV_UNIX
        static void            vProc           (const std::tstring_t &csProcPath, std::vec_tstring_t *pvsData);
            ///< get from UNIX proc file content
        static std::tstring_t  sProcValue      (const std::tstring_t &csProcPath, const std::tstring_t &csData);
            ///< get from UNIX proc file content value by data
    #endif

    private:
        std::tstring_t        _m_sFilePath;

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxPathH
