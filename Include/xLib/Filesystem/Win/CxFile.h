/**
 * \file  CxFile.h
 * \brief file
 */


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

        BOOL             bCreate             (const std::tstring &csFilePath, ULONG ulAccess/* = grWrite*/, ULONG ulShareMode/* = smDenyAll*/, ULONG ulFlags/* = cfCreateAlways*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
        BOOL             bTryOpen            (const std::tstring &csFilePath, ULONG ulAccess/* = grRead*/,  ULONG ulShareMode/* = smRead*/,    ULONG ulFlags/* = cfOpenExisting*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
        BOOL             bOpen               (const std::tstring &csFilePath, ULONG ulAccess/* = grRead*/,  ULONG ulShareMode/* = smRead*/,    ULONG ulFlags/* = cfOpenExisting*/, CxFileAttribute::EAttribute atAttributes/* = faNormal*/);
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

        static BOOL      bIsExists           (const std::tstring &csFilePath);
        static std::tstring   sIsExists           (const std::tstring &csFilePath);
        static ETypeEx   tpGetTypeEx         (const std::tstring &csFilePath);
        static LONGLONG  llGetSize           (const std::tstring &csFilePath);

        static BOOL      bDelete             (const std::tstring &csFilePath);
        static BOOL      bMove               (const std::tstring &csFilePathIn, const std::tstring &csFilePathOut);
        static std::tstring   sCreateTempName     (const std::tstring &csPrefix);
        static BOOL      bCopy               (const std::tstring &csFilePathFrom, const std::tstring &csFilePathTo);
        static BOOL      bCopy               (const std::tstring &csFilePathFrom, const std::tstring &csFilePathTo, BOOL bFailIfExists);
        static BOOL      bReplace            (const std::tstring &csOldFileName, const std::tstring &csNewFilePath, const std::tstring &csBackupFilePath);
        static BOOL      bWipe               (const std::tstring &csFilePath, UINT uiPasses);
        static BOOL      bSetRandomDate      (const std::tstring &csFilePath);
        static ULONGLONG ullGetCompressedSize(const std::tstring &csFilePath);


        /****************************************************************************
        * ��������
        *
        *****************************************************************************/

        static BOOL      bSetAttrUncompressed(const std::tstring &csFilePath);
        static BOOL      bSetAttrCompressed  (const std::tstring &csFilePath, BOOL bCompress);

        static std::tstring   sReadText           (const std::tstring &csFilePath);
        static bool      bWriteText          (const std::tstring &csFilePath, const std::tstring &csText);

        //other
        static BOOL      bBackup             (const std::tstring &csFilePath, const std::tstring &csDestDirPath, BOOL bMakeDaily /*,INT bBackupLimit*/);
        static BOOL      bExec               (const std::tstring &csFilePath, const std::tstring &csParams);

    private:
        BOOL             _m_bRes;
        static BOOL      _ms_bRes;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxFileH
