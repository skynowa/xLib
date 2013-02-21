/**
 * \file  CxPath.h
 * \brief file system path
 */


#ifndef xLib_Filesystem_CxPathH
#define xLib_Filesystem_CxPathH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
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

    const std::tstring_t & filePath       () const xWARN_UNUSED_RESULT;
        ///< file path

#if xOS_ENV_WIN
    std::tstring_t         drive          () const xWARN_UNUSED_RESULT;
        ///< get drive
#endif
    std::tstring_t         dir            () const xWARN_UNUSED_RESULT;
        ///< get dir path, without a trailing backslash '\'
    std::tstring_t         dirName        () const xWARN_UNUSED_RESULT;
        ///< get dir name
    std::tstring_t         fileName       () const xWARN_UNUSED_RESULT;
        ///< get name.extension
    std::tstring_t         fileBaseName   () const xWARN_UNUSED_RESULT;
        ///< get name without extension
    std::tstring_t         ext            () const xWARN_UNUSED_RESULT;
        ///< get extension

#if xOS_ENV_WIN
    std::tstring_t         setDrive       (const std::tstring_t &csDrivePath) xWARN_UNUSED_RESULT;
        ///< set drive
#endif
    std::tstring_t         setDir         (const std::tstring_t &csDirPath) xWARN_UNUSED_RESULT;
        ///< set dir
    std::tstring_t         setFileName    (const std::tstring_t &csFullName) xWARN_UNUSED_RESULT;
        ///< set full name
    std::tstring_t         setFileBaseName(const std::tstring_t &csName) xWARN_UNUSED_RESULT;
        ///< set name
    std::tstring_t         setExt         (const std::tstring_t &csExt) xWARN_UNUSED_RESULT;
        ///< set extension

    std::tstring_t         removeExt      () xWARN_UNUSED_RESULT;
        ///< remove extension
    std::tstring_t         removeExtIf    (const std::tstring_t &csExt) xWARN_UNUSED_RESULT;
        ///< remove extension if it equal some string


    bool                   isAbsolute     () const xWARN_UNUSED_RESULT;
        ///< is absolute

    std::tstring_t         toWin          (const bool &cbIsSlashAtEnd) const xWARN_UNUSED_RESULT;
        ///< convert slashes to Windows style
    std::tstring_t         toUnix         (const bool &cbIsSlashAtEnd) const xWARN_UNUSED_RESULT;
        ///< convert slashes to Nix style
    std::tstring_t         toNative       (const bool &cbIsSlashAtEnd) const xWARN_UNUSED_RESULT;
        ///< convert slashes to native style
    std::tstring_t         absolute       () const xWARN_UNUSED_RESULT;
        ///< get absolute path
    std::tstring_t         brief          (const size_t &cuiMaxSize) const xWARN_UNUSED_RESULT;
        ///< get short path

    std::tstring_t         slashAppend    () const xWARN_UNUSED_RESULT;
        ///< append slash
    std::tstring_t         slashRemove    () const xWARN_UNUSED_RESULT;
        ///< remove slash

    // static
    static std::tstring_t  exe            () xWARN_UNUSED_RESULT;
        ///< get full path to exe
    static std::tstring_t  exeDir         () xWARN_UNUSED_RESULT;
        ///< get dir path to exe
    static std::tstring_t  dll            () xWARN_UNUSED_RESULT;
        ///< get full path to dll
    static std::tstring_t  standartExt    (const ExStandartExt &cseFileExt) xWARN_UNUSED_RESULT;
        ///< get standard extension

    static bool            isValid        (const std::tstring_t &csFilePath) xWARN_UNUSED_RESULT;
        ///< path validation
    static bool            isNameValid    (const std::tstring_t &csFileName) xWARN_UNUSED_RESULT;
        ///< name validation

    static std::tstring_t  shortName      (const std::tstring_t &csFileName, const size_t &cuiMaxSize) xWARN_UNUSED_RESULT;
        ///< get short name
    static std::tstring_t  setNameValid   (const std::tstring_t &csFileName) xWARN_UNUSED_RESULT;
        ///< set name as valid

    static size_t          maxSize        ();
        ///< get max path length in symbols
    static size_t          nameMaxSize    ();
        ///< get max name length in symbols

#if xOS_ENV_UNIX
    static void            proc           (const std::tstring_t &csProcPath, std::vec_tstring_t *pvsData);
        ///< get from UNIX proc file content
    static std::tstring_t  procValue      (const std::tstring_t &csProcPath, const std::tstring_t &csData) xWARN_UNUSED_RESULT;
        ///< get from UNIX proc file content value by data
#endif

private:
    std::tstring_t         _m_sFilePath;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxPathH
