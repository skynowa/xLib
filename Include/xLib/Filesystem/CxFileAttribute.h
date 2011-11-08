/**
 * \file  CxFileAttribute.h
 * \brief file attribute
 */


#ifndef xLib_Filesystem_CxFileAttributeH
#define xLib_Filesystem_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxFileAttribute :
    public CxNonCopyable
    /// file attribute
{
    public:
        enum EAttribute
            /// attribute
        {
            //TODO: separate writable and readable attributes
            #if defined(xOS_ENV_WIN)
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
            #elif defined(xOS_ENV_UNIX)
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

        static BOOL       bIsExists      (const std::string_t &csFilePath, const EAttribute cfaValue);
            ///< is exists
        static EAttribute atGet          (const std::string_t &csFilePath);
            ///< get
        static BOOL       bSet           (const std::string_t &csFilePath, const EAttribute cfaValue);
            ///< set
        static BOOL       bAdd           (const std::string_t &csFilePath, const EAttribute cfaValue);
            ///< add
        static BOOL       bRemove        (const std::string_t &csFilePath, const EAttribute cfaValue);
            ///< remove
        static BOOL       bModify        (const std::string_t &csFilePath, const EAttribute cfaRemoveValue, const EAttribute cfaAddValue);
            ///< modify
        static BOOL       bClear         (const std::string_t &csFilePath);
            ///< clear

    private:
                          CxFileAttribute();
            ///< constructor
        virtual          ~CxFileAttribute();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxFileAttributeH
