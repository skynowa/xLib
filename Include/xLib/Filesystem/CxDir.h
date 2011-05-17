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
class CxDir : public CxNonCopyable {
    public:
        static BOOL    bIsExists    (const tString &csDirPath);
        static BOOL    bIsEmpty     (const tString &csDirPath, const tString &csMask = CxConst::xMASK_ALL);
        //static BOOL  bIsRoot      (const tString &csDirPath);
        static BOOL    bIsDir       (const tString &csDirPath);
        static tString sGetCurrent  ();
        static BOOL    bSetCurrent  (const tString &csDirPath);
        static tString sGetTempPath ();
        static BOOL    bCreate      (const tString &csDirPath);
        static BOOL    bCreateForce (const tString &csDirPath);
        static BOOL    bCopy        (const tString &csFromDirPath, const tString &csToDirPath, BOOL bFailIfExists);
        static BOOL    bMove        (const tString &csInDirPath,   const tString &csOutDirPath);

        static BOOL    bDelete      (const tString &csDirPath);
        static BOOL    bClearForce  (const tString &csDirPath);
        static BOOL    bDeleteForce (const tString &csDirPath);

        static BOOL    bFindFiles   (const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsFilePathes);
        static BOOL    bFindDirs    (const tString &csDirPath, const tString &cMask, BOOL bIsRecurse, std::vector<tString> *pvecsDirPathes);

    private:
                       CxDir        ();
        virtual       ~CxDir        ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
