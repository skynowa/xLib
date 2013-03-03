/**
 * \file  CxFileAttribute.h
 * \brief file attribute
 */


#ifndef xLib_Filesystem_CxFileAttributeH
#define xLib_Filesystem_CxFileAttributeH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFileAttribute :
    private CxNonCopyable
    /// file attribute
{
public:
    enum ExAttribute
        /// attribute
    {
        #if   xOS_ENV_WIN
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
        #elif xOS_ENV_UNIX
            faInvalid           = - 1,
            faNormal            = 0755,
            faReadOnly          = 0444,
            faDirectory         = S_IFDIR,
            faBlockDevice       = S_IFBLK,
            faSocket            = S_IFSOCK,
            faSymbolicLink      = S_IFLNK,
            faRegularFile       = S_IFREG,
            faCharacterDevice   = S_IFCHR,
            faFifo              = S_IFIFO
        #endif
    };

    explicit          CxFileAttribute(std::ctstring_t &csFilePath);
        ///< constructor
    virtual          ~CxFileAttribute();
        ///< destructor

    std::ctstring_t & filePath       () const xWARN_UNUSED_RV;
        ///< file path

    bool_t            isExists       (const ExAttribute &cfaValue) xWARN_UNUSED_RV;
        ///< is exists
    ExAttribute       get            () xWARN_UNUSED_RV;
        ///< get
    void_t            set            (const ExAttribute &cfaValue);
        ///< set
    void_t            add            (const ExAttribute &cfaValue);
        ///< add
    void_t            remove         (const ExAttribute &cfaValue);
        ///< remove
    void_t            modify         (const ExAttribute &cfaRemoveValue, const ExAttribute &cfaAddValue);
        ///< modify
    void_t            clear          ();
        ///< clear (set normal attributes)

private:
    std::ctstring_t   _m_csFilePath;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxFileAttributeH
