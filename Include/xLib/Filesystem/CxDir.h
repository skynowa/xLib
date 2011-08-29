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
    /// directory
{
    public:
        static BOOL         bIsExists   (const std::tstring &csDirPath);
            ///< check for existence
        static BOOL         bIsEmpty    (const std::tstring &csDirPath, const std::tstring &csMask = CxConst::xMASK_ALL);
            ///< is empty
        static BOOL         bIsRoot     (const std::tstring &csDirPath);
            ///< is root
        static BOOL         bIsDir      (const std::tstring &csDirPath);
            ///< is dir
        static std::tstring sGetCurrent ();
            ///< get current
        static BOOL         bSetCurrent (const std::tstring &csDirPath);
            ///< set current
        static std::tstring sGetTemp    ();
            ///< get path to system var %Temp%
        static BOOL         bCreate     (const std::tstring &csDirPath);
            ///< create
        static BOOL         bCreateForce(const std::tstring &csDirPath);
            ///< creation of all dirs that not exists in path
        static BOOL         bCopy       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const BOOL cbFailIfExists);
            ///< copy
        static BOOL         bMove       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const BOOL cbFailIfExists);
            ///< move

        static BOOL         bDelete     (const std::tstring &csDirPath);
            ///< deletion dir which empty
        static BOOL         bTryDelete  (const std::tstring &csDirPath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static BOOL         bClearForce (const std::tstring &csDirPath);
            ///< detetion all content of dir
        static BOOL         bDeleteForce(const std::tstring &csDirPath);
            ///< detetion dir fnd all content of it

        static BOOL         bFindFiles  (const std::tstring &csDirPath, const std::tstring &cMask, const BOOL cbIsRecurse, std::vector<std::tstring> *pvsFilePathes);
            ///< search files
        static BOOL         bFindDirs   (const std::tstring &csDirPath, const std::tstring &cMask, const BOOL cbIsRecurse, std::vector<std::tstring> *pvsDirPathes);
            ///< search subdirs

    private:
                            CxDir       ();
            ///< constructor
        virtual            ~CxDir       ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
