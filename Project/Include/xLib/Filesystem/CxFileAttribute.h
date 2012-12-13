/**
 * \file  CxFileAttribute.h
 * \brief file attribute
 */


#ifndef xLib_Filesystem_CxFileAttributeH
#define xLib_Filesystem_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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

        static bool        bIsExists      (const std::tstring_t &csFilePath, const ExAttribute &cfaValue);
            ///< is exists
        static ExAttribute atGet          (const std::tstring_t &csFilePath);
            ///< get
        static void        vSet           (const std::tstring_t &csFilePath, const ExAttribute &cfaValue);
            ///< set
        static void        vAdd           (const std::tstring_t &csFilePath, const ExAttribute &cfaValue);
            ///< add
        static void        vRemove        (const std::tstring_t &csFilePath, const ExAttribute &cfaValue);
            ///< remove
        static void        vModify        (const std::tstring_t &csFilePath, const ExAttribute &cfaRemoveValue, const ExAttribute &cfaAddValue);
            ///< modify
        static void        vClear         (const std::tstring_t &csFilePath);
            ///< clear (set normal attributes)

    private:
                           CxFileAttribute();
            ///< constructor
        virtual           ~CxFileAttribute();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxFileAttributeH
