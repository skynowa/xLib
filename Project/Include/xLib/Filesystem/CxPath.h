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

    explicit               CxPath         (const std::tstring_t &csFilePath);
        ///< constructor
    virtual               ~CxPath         ();
        ///< destructor

    const std::tstring_t & filePath       () const;
        ///< file path

#if xOS_ENV_WIN
    std::tstring_t         drive          () const;
        ///< get drive
#endif
    std::tstring_t         dir            () const;
        ///< get dir path, without a trailing backslash '\'
    std::tstring_t         dirName        () const;
        ///< get dir name
    std::tstring_t         fileName       () const;
        ///< get name.extension
    std::tstring_t         fileBaseName   () const;
        ///< get name without extension
    std::tstring_t         ext            () const;
        ///< get extension

#if xOS_ENV_WIN
    std::tstring_t         setDrive       (const std::tstring_t &csDrivePath);
        ///< set drive
#endif
    std::tstring_t         setDir         (const std::tstring_t &csDirPath);
        ///< set dir
    std::tstring_t         setFileName    (const std::tstring_t &csFullName);
        ///< set full name
    std::tstring_t         setFileBaseName(const std::tstring_t &csName);
        ///< set name
    std::tstring_t         setExt         (const std::tstring_t &csExt);
        ///< set extension

    std::tstring_t         removeExt      ();
        ///< remove extension
    std::tstring_t         removeExtIf    (const std::tstring_t &csExt);
        ///< remove extension if it equal some string


    bool                   isAbsolute     () const;
        ///< is absolute

    std::tstring_t         toWin          (const bool &cbIsSlashAtEnd) const;
        ///< convert slashes to Windows style
    std::tstring_t         toUnix         (const bool &cbIsSlashAtEnd) const;
        ///< convert slashes to Nix style
    std::tstring_t         toNative       (const bool &cbIsSlashAtEnd) const;
        ///< convert slashes to native style
    std::tstring_t         absolute       () const;
        ///< get absolute path
    std::tstring_t         brief          (const size_t &cuiMaxSize) const;
        ///< get short path

    std::tstring_t         slashAppend    () const;
        ///< append slash
    std::tstring_t         slashRemove    () const;
        ///< remove slash

    // static
    static std::tstring_t  exe            ();
        ///< get full path to exe
    static std::tstring_t  exeDir         ();
        ///< get dir path to exe
    static std::tstring_t  dll            ();
        ///< get full path to dll
    static std::tstring_t  standartExt    (const ExStandartExt &cseFileExt);
        ///< get standard extension

    static bool            isValid        (const std::tstring_t &csFilePath);
        ///< path validation
    static bool            isNameValid    (const std::tstring_t &csFileName);
        ///< name validation

    static std::tstring_t  shortName      (const std::tstring_t &csFileName, const size_t &cuiMaxSize);
        ///< get short name
    static std::tstring_t  setNameValid   (const std::tstring_t &csFileName);
        ///< set name as valid

    static size_t          maxSize        ();
        ///< get max path length in symbols
    static size_t          nameMaxSize    ();
        ///< get max name length in symbols

#if xOS_ENV_UNIX
    static void            proc           (const std::tstring_t &csProcPath, std::vec_tstring_t *pvsData);
        ///< get from UNIX proc file content
    static std::tstring_t  procValue      (const std::tstring_t &csProcPath, const std::tstring_t &csData);
        ///< get from UNIX proc file content value by data
#endif

private:
    std::tstring_t         _m_sFilePath;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxPathH
