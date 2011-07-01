/****************************************************************************
* Class name:  CxFile
* Description: file
* File name:   CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     03.06.2009 16:30:15
*
*****************************************************************************/


#ifndef xLib_Filesystem_Win_CxFileH
#define xLib_Filesystem_Win_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Filesystem/CxFileAttribute.h>

#if defined(xOS_WIN)
    #include <xLib/Common/Win/CxHandleT.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxFile :
    public CxNonCopyable
{
    public:
        enum EGenericRights {
            grAll     = GENERIC_ALL,
            grExecute = GENERIC_EXECUTE,
            grRead    = GENERIC_READ,
            grWrite   = GENERIC_WRITE
        };

        enum EShareMode {
            smDenyAll = 0,
            smDelete  = FILE_SHARE_DELETE,
            smRead    = FILE_SHARE_READ,
            smWrite   = FILE_SHARE_WRITE
        };

        enum ECreationFlags {
            cfCreateAlways  = CREATE_ALWAYS,
            cfCreateNew     = CREATE_NEW,
            cfOpenAlways    = OPEN_ALWAYS,
            cfOpenExisting  = OPEN_EXISTING,
            cfTruncExisting = TRUNCATE_EXISTING,
        };

        enum EPointerPosition {
            ppBegin = FILE_BEGIN,
            ppCurr  = FILE_CURRENT,
            ppEnd   = FILE_END
        };

        enum EType {
            ftChar    = FILE_TYPE_CHAR,
            ftDisk    = FILE_TYPE_DISK,
            ftPipe    = FILE_TYPE_PIPE,
            ftRemote  = FILE_TYPE_REMOTE,
            ftUnknown = FILE_TYPE_UNKNOWN
        };

        enum ETypeEx {
            fteUnknown = 0,
            fteFile    = 1,
            fteDir     = 2
        };

        CxFileHandle     m_hHandle;


                         CxFile              ();
        virtual         ~CxFile              ();

        BOOL             bCreate             (const tString &csFilePath, ULONG ulAccess/* = grWrite*/, ULONG ulShareMode/* = smDenyAll*/, ULONG ulFlags/* = cfCreateAlways*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
        BOOL             bTryOpen            (const tString &csFilePath, ULONG ulAccess/* = grRead*/,  ULONG ulShareMode/* = smRead*/,    ULONG ulFlags/* = cfOpenExisting*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
        BOOL             bOpen               (const tString &csFilePath, ULONG ulAccess/* = grRead*/,  ULONG ulShareMode/* = smRead*/,    ULONG ulFlags/* = cfOpenExisting*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
        BOOL             bClose              ();
        BOOL             bIsOpen             ();
        BOOL             bIsEmpty            ();

        BOOL             bRead               (LPVOID pvBuf, ULONG ulCount);
        BOOL             bRead               (LPVOID pvBuf, ULONG ulCount, LPDWORD pulRead);
        BOOL             bWrite              (LPCVOID pcvBuf, ULONG ulCount);
        BOOL             bWrite              (LPCVOID pcvBuf, ULONG ulCount, LPDWORD pulWritten);
        ULONG            ulSetPosition       (LONG liOff, EPointerPosition fpPos);
        ULONG            ulGetPosition       ();
        BOOL             bLock               (ULONG ulOffset, ULONG ulSize);
        BOOL             bUnlock             (ULONG ulOffset, ULONG ulSize);
        BOOL             bSetEof             ();
        BOOL             bFlush              ();
        LONGLONG         llGetSize           ();
        BOOL             bSetSize            (ULONG ulSize);
        ULONG            ulGetType           ();
        BOOL             bGetTime            (FILETIME *pftCreate, FILETIME *pftAccess, FILETIME *pftModified);
        BOOL             bSetTime            (const FILETIME &cftCreate, const FILETIME &cftAccess, const FILETIME &cftModified);

        static BOOL      bIsExists           (const tString &csFilePath);
        static tString   sIsExists           (const tString &csFilePath);
        static ETypeEx   tpGetTypeEx         (const tString &csFilePath);
        static LONGLONG  llGetSize           (const tString &csFilePath);

        static BOOL      bDelete             (const tString &csFilePath);
        static BOOL      bMove               (const tString &csFilePathIn, const tString &csFilePathOut);
        static tString   sCreateTempName     (const tString &csPrefix);
        static BOOL      bCopy               (const tString &csFilePathFrom, const tString &csFilePathTo);
        static BOOL      bCopy               (const tString &csFilePathFrom, const tString &csFilePathTo, BOOL bFailIfExists);
        static BOOL      bReplace            (const tString &csOldFileName, const tString &csNewFilePath, const tString &csBackupFilePath);
        static BOOL      bWipe               (const tString &csFilePath, UINT uiPasses);
        static BOOL      bSetRandomDate      (const tString &csFilePath);
        static ULONGLONG ullGetCompressedSize(const tString &csFilePath);


        /****************************************************************************
        * ��������
        *
        *****************************************************************************/

        static BOOL      bSetAttrUncompressed(const tString &csFilePath);
        static BOOL      bSetAttrCompressed  (const tString &csFilePath, BOOL bCompress);

        static tString   sReadText           (const tString &csFilePath);
        static bool      bWriteText          (const tString &csFilePath, const tString &csText);

        //other
        static BOOL      bBackup             (const tString &csFilePath, const tString &csDestDirPath, BOOL bMakeDaily /*,INT bBackupLimit*/);
        static BOOL      bExec               (const tString &csFilePath, const tString &csParams);

    private:
        BOOL             _m_bRes;
        static BOOL      _ms_bRes;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxFileH
