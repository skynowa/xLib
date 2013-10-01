/**
 * \file  CxFileType.h
 * \brief file type
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFileType :
    private CxNonCopyable
    /// file attribute
{
public:
    enum ExType
        /// attribute
    {
        #if xOS_ENV_WIN
            faInvalid           = INVALID_FILE_ATTRIBUTES,
            faNormal            = FILE_ATTRIBUTE_NORMAL,
            faReadOnly          = FILE_ATTRIBUTE_READONLY,
            faHidden            = FILE_ATTRIBUTE_HIDDEN,
            faSystem            = FILE_ATTRIBUTE_SYSTEM,
            faDirectory         = FILE_ATTRIBUTE_DIRECTORY,
            faArchive           = FILE_ATTRIBUTE_ARCHIVE,
            faDevice            = FILE_ATTRIBUTE_DEVICE,
            faTemporary         = FILE_ATTRIBUTE_TEMPORARY,
            faSparseFile        = FILE_ATTRIBUTE_SPARSE_FILE,
            faReparsePoint      = FILE_ATTRIBUTE_REPARSE_POINT,
            faCompressed        = FILE_ATTRIBUTE_COMPRESSED,
            faOffline           = FILE_ATTRIBUTE_OFFLINE,
            faNotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
            faEncrypted         = FILE_ATTRIBUTE_ENCRYPTED
        #else
            faInvalid           = (mode_t)- 1,
            faDirectory         = S_IFDIR,
            faCharacterDevice   = S_IFCHR,
            faBlockDevice       = S_IFBLK,
            faRegularFile       = S_IFREG,
            faFifo              = S_IFIFO,
            faSymbolicLink      = S_IFLNK,
            faSocket            = S_IFSOCK
        #endif
    };
    typedef const ExType cExType;

#if xOS_ENV_WIN
    typedef DWORD  types_t;
#else
    typedef mode_t types_t;
#endif

    typedef const types_t ctypes_t;
        ///< all types

    explicit          CxFileType(std::ctstring_t &csFilePath);
        ///< constructor
    virtual          ~CxFileType();
        ///< destructor

    std::ctstring_t & filePath  () const xWARN_UNUSED_RV;
        ///< file path

    bool_t            isExists  (cExType &cftValue) xWARN_UNUSED_RV;
        ///< is exists
    types_t           get       () xWARN_UNUSED_RV;
        ///< get
    void_t            set       (ctypes_t &cftValues);
        ///< set
    void_t            add       (cExType &cftValue);
        ///< add
    void_t            remove    (cExType &cftValue);
        ///< remove
    void_t            modify    (cExType &cftRemoveValue, cExType &cftAddValue);
        ///< modify
    void_t            clear     ();
        ///< clear (set normal attributes, only for Windows)

private:
    std::ctstring_t   _m_csFilePath;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
