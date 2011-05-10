/****************************************************************************
* Class name:  CxFile
* Description: file
* File name:   CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     03.06.2009 16:30:15
*
*****************************************************************************/


#ifndef xLib_Fso_CxFileH
#define xLib_Fso_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/Win/CxHandle.h>
#include <xLib/Filesystem/CxFileAttribute.h>
//---------------------------------------------------------------------------
class CxFile : public CxNonCopyable {
    public:
        //generic rights
        enum EGenericRights {
            grAll     = GENERIC_ALL,                //Read, write, and execute access
            grExecute = GENERIC_EXECUTE,            //Execute access
            grRead    = GENERIC_READ,                //Read access
            grWrite   = GENERIC_WRITE                //Write access
        };

        //share modes
        enum EShareMode {
            smDenyAll = 0,                            //Prevents other processes from opening a file or device if they request delete, read, or write access.
            smDelete  = FILE_SHARE_DELETE,            //Enables subsequent open operations on a file or device to request delete access.
            smRead    = FILE_SHARE_READ,            //Enables subsequent open operations on a file or device to request read access.
            smWrite   = FILE_SHARE_WRITE            //Enables subsequent open operations on a file or device to request write access.
        };

        //Creation flags
        enum ECreationFlags {
            cfCreateAlways  = CREATE_ALWAYS,        //Creates a new file, always.
            cfCreateNew     = CREATE_NEW,            //Creates a new file, only if it does not already exist.
            cfOpenAlways    = OPEN_ALWAYS,            //Opens a file, always.
            cfOpenExisting  = OPEN_EXISTING,        //Opens a file or device, only if it exists.
            cfTruncExisting = TRUNCATE_EXISTING,    //Opens a file and truncates it so that its size is zero bytes, only if it exists.
        };

        //file position data for the given stream
        enum EPointerPosition {
            ppBegin = FILE_BEGIN,
            ppCurr  = FILE_CURRENT,
            ppEnd   = FILE_END,
        };

        //file types
        enum EType {
            ftChar    = FILE_TYPE_CHAR,                //character file, typically an LPT device or a console.
            ftDisk    = FILE_TYPE_DISK,                 //disk file.
            ftPipe    = FILE_TYPE_PIPE,             //socket, a named pipe, or an anonymous pipe.
            ftRemote  = FILE_TYPE_REMOTE,           //Unused.
            ftUnknown = FILE_TYPE_UNKNOWN            //unknown, or the function failed.
        };

        //file type
        enum ETypeEx {
            fteUnknown = 0,
            fteFile    = 1,
            fteDir     = 2
        };

        CxHandle m_hHandle;


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
        BOOL             bSetTime            (FILETIME *pftCreate, FILETIME *pftAccess, FILETIME *pftModified);

        static BOOL      bIsExists           (const tString &csFilePath);
        static tString   sIsExists           (const tString &csFilePath);
        static ETypeEx   tpGetTypeEx         (const tString &csFilePath);
        static LONGLONG  llGetSize           (const tString &csFilePath);

        static BOOL      bDelete             (const tString &csFilePath);
        static BOOL      bMove               (const tString &csFilePathIn, const tString &csFilePathOut); //����, �������
        static tString   sCreateTempName     (const tString &csPrefix);
        static BOOL      bCopy               (const tString &csFilePathFrom, const tString &csFilePathTo);
        static BOOL      bCopy               (const tString &csFilePathFrom, const tString &csFilePathTo, BOOL bFailIfExists);
        static BOOL      bReplace            (const tString &csOldFileName, const tString &csNewFilePath, const tString &csBackupFilePath);
        static BOOL      bWipe               (const tString &csFilePath, UINT uiPasses); /*-*/
        ////static BOOL      bCutFromEnd         (const tString &csFilePath, LONG lDistanceToCut);
        ////static BOOL      bCutFromEnd         (FILE *pFile, ULONG ulDistanceToCut);
        ////static BOOL      bCheckSignature     (LPCTSTR pcszBuff, LPCTSTR pcszSignature, INT iSignatureSize);
        static BOOL      bSetRandomDate      (const tString &csFilePath);
        static ULONGLONG ullGetCompressedSize(const tString &csFilePath);


        /****************************************************************************
        * ��������
        *
        *****************************************************************************/

        static BOOL         bSetAttrUncompressed(const tString &csFilePath);
        static BOOL         bSetAttrCompressed  (const tString &csFilePath, BOOL bCompress);

        static tString     sReadText            (const tString &csFilePath);
        static bool         bWriteText           (const tString &csFilePath, const tString &csText);

        //other
        static BOOL      bBackup             (const tString &csFilePath, const tString &csDestDirPath, BOOL bMakeDaily /*,INT bBackupLimit*/);
        static BOOL      bExec               (const tString &csFilePath, const tString &csParams);

    private:
        BOOL             _m_bRes;
        static BOOL      _ms_bRes;
};
//---------------------------------------------------------------------------
#endif    //xLib_Fso_CxFileH
