/****************************************************************************
* Class name:  CxDir
* Description: directory
* File name:   CxDir.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     04.06.2009 9:23:33
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxDirH
#define xLib_Filesystem_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDir :
    public CxNonCopyable
{
    public:
        static BOOL    bIsExists   (const tString &csDirPath);
        static BOOL    bIsEmpty    (const tString &csDirPath, const tString &csMask = CxConst::xMASK_ALL);
        static BOOL    bIsRoot     (const tString &csDirPath);
        static BOOL    bIsDir      (const tString &csDirPath);
        static tString sGetCurrent ();
        static BOOL    bSetCurrent (const tString &csDirPath);
        static tString sGetTemp    ();
        static BOOL    bCreate     (const tString &csDirPath);
        static BOOL    bCreateForce(const tString &csDirPath);
        static BOOL    bCopy       (const tString &csDirPathFrom, const tString &csDirPathTo, const BOOL cbFailIfExists);
        static BOOL    bMove       (const tString &csDirPathFrom, const tString &csDirPathTo, const BOOL cbFailIfExists);

        static BOOL    bDelete     (const tString &csDirPath);
        static BOOL    bTryDelete  (const tString &csDirPath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
        static BOOL    bClearForce (const tString &csDirPath);
        static BOOL    bDeleteForce(const tString &csDirPath);

        static BOOL    bFindFiles  (const tString &csDirPath, const tString &cMask, const BOOL cbIsRecurse, std::vector<tString> *pvsFilePathes);
        static BOOL    bFindDirs   (const tString &csDirPath, const tString &cMask, const BOOL cbIsRecurse, std::vector<tString> *pvsDirPathes);

    private:
                       CxDir       ();
        virtual       ~CxDir       ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
