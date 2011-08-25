/**
 * \file  CxDir.h
 * \brief directory
 */


#ifndef xLib_Filesystem_CxDirH
#define xLib_Filesystem_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxDir :
    public CxNonCopyable
{
    public:
        static BOOL    bIsExists   (const std::tstring &csDirPath);
        static BOOL    bIsEmpty    (const std::tstring &csDirPath, const std::tstring &csMask = CxConst::xMASK_ALL);
        static BOOL    bIsRoot     (const std::tstring &csDirPath);
        static BOOL    bIsDir      (const std::tstring &csDirPath);
        static std::tstring sGetCurrent ();
        static BOOL    bSetCurrent (const std::tstring &csDirPath);
        static std::tstring sGetTemp    ();
        static BOOL    bCreate     (const std::tstring &csDirPath);
        static BOOL    bCreateForce(const std::tstring &csDirPath);
        static BOOL    bCopy       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const BOOL cbFailIfExists);
        static BOOL    bMove       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const BOOL cbFailIfExists);

        static BOOL    bDelete     (const std::tstring &csDirPath);
        static BOOL    bTryDelete  (const std::tstring &csDirPath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
        static BOOL    bClearForce (const std::tstring &csDirPath);
        static BOOL    bDeleteForce(const std::tstring &csDirPath);

        static BOOL    bFindFiles  (const std::tstring &csDirPath, const std::tstring &cMask, const BOOL cbIsRecurse, std::vector<std::tstring> *pvsFilePathes);
        static BOOL    bFindDirs   (const std::tstring &csDirPath, const std::tstring &cMask, const BOOL cbIsRecurse, std::vector<std::tstring> *pvsDirPathes);

    private:
                       CxDir       ();
        virtual       ~CxDir       ();
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
