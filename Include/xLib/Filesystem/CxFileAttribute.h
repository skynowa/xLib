/****************************************************************************
* Class name:  CxFileAttribute
* Description: file attribute
* File name:   CxFileAttribute.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.04.2010 13:37:54
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxFileAttributeH
#define xLib_Filesystem_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxFileAttribute : public CxNonCopyable {
    public:
        enum EAttribute {
            #if defined(xOS_WIN)
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
            #elif defined(xOS_LINUX)
                faInvalid           = - 1,
                faNormal            = 0755,
                faReadOnly          = 0444,
                faHidden            = 04000,
                faSystem            = 02000,
                faDirectory         = S_IFDIR,
                faArchive           = 01000,
                faBlockDevice       = S_IFBLK,
                faTemporary         = 01000000,
                faSparseFile        = 04000000,
                //faReparsePoint      = ,
                faCompressed        = 02000000,
                //faOffline           = ,
                //faNotContentIndexed = ,
                //faEncrypted         = ,
                faSocket            = S_IFSOCK,
                faSymbolicLink      = S_IFLNK,
                faRegularFile       = S_IFREG,
                faCharacterDevice   = S_IFCHR,
                faFifo              = S_IFIFO
            #endif
        };

        static BOOL       bIsExists      (const tString &csFilePath, const EAttribute cfaValue);
        static EAttribute atGet          (const tString &csFilePath);
        static BOOL       bSet           (const tString &csFilePath, const EAttribute cfaValue);
        static BOOL       bAdd           (const tString &csFilePath, const EAttribute cfaValue);
        static BOOL       bRemove        (const tString &csFilePath, const EAttribute cfaValue);
        static BOOL       bModify        (const tString &csFilePath, const EAttribute cfaRemoveValue, const EAttribute cfaAddValue);
        static BOOL       bClear         (const tString &csFilePath);

    private:
                          CxFileAttribute();
        virtual          ~CxFileAttribute();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxFileAttributeH
