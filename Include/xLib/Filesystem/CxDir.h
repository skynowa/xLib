/**
 * \file  CxDir.h
 * \brief directory
 */


#ifndef xLib_Filesystem_CxDirH
#define xLib_Filesystem_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDir :
    public CxNonCopyable
    /// directory
{
    public:
        static bool         bIsExists   (const std::tstring &csDirPath);
            ///< check for existence
        static bool         bIsEmpty    (const std::tstring &csDirPath, const std::tstring &csMask = CxConst::xMASK_ALL);
            ///< is empty
        static bool         bIsRoot     (const std::tstring &csDirPath);
            ///< is root
        static bool         bIsDir      (const std::tstring &csDirPath);
            ///< is dir
        static std::tstring sGetCurrent ();
            ///< get current
        static bool         bSetCurrent (const std::tstring &csDirPath);
            ///< set current
        static std::tstring sGetTemp    ();
            ///< get path to system var %Temp%
        static bool         bCreate     (const std::tstring &csDirPath);
            ///< create
        static bool         bCreateForce(const std::tstring &csDirPath);
            ///< creation of all dirs that not exists in path
        static bool         bCopy       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const bool cbFailIfExists);
            ///< copy
        static bool         bMove       (const std::tstring &csDirPathFrom, const std::tstring &csDirPathTo, const bool cbFailIfExists);
            ///< move

        static bool         bDelete     (const std::tstring &csDirPath);
            ///< deletion dir which empty
        static bool         bTryDelete  (const std::tstring &csDirPath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static bool         bClearForce (const std::tstring &csDirPath);
            ///< detetion all content of dir
        static bool         bDeleteForce(const std::tstring &csDirPath);
            ///< detetion dir fnd all content of it

        static bool         bFindFiles  (const std::tstring &csDirPath, const std::tstring &cMask, const bool cbIsRecurse, std::vector<std::tstring> *pvsFilePathes);
            ///< search files
        static bool         bFindDirs   (const std::tstring &csDirPath, const std::tstring &cMask, const bool cbIsRecurse, std::vector<std::tstring> *pvsDirPathes);
            ///< search subdirs

    private:
                            CxDir       ();
            ///< constructor
        virtual            ~CxDir       ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
