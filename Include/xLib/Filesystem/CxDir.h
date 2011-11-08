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
        static BOOL         bIsExists   (const std::string_t &csDirPath);
            ///< check for existence
        static BOOL         bIsEmpty    (const std::string_t &csDirPath, const std::string_t &csMask = CxConst::xMASK_ALL);
            ///< is empty
        static BOOL         bIsRoot     (const std::string_t &csDirPath);
            ///< is root
        static BOOL         bIsDir      (const std::string_t &csDirPath);
            ///< is dir
        static std::string_t sGetCurrent ();
            ///< get current
        static BOOL         bSetCurrent (const std::string_t &csDirPath);
            ///< set current
        static std::string_t sGetTemp    ();
            ///< get path to system var %Temp%
        static BOOL         bCreate     (const std::string_t &csDirPath);
            ///< create
        static BOOL         bCreateForce(const std::string_t &csDirPath);
            ///< creation of all dirs that not exists in path
        static BOOL         bCopy       (const std::string_t &csDirPathFrom, const std::string_t &csDirPathTo, const BOOL cbFailIfExists);
            ///< copy
        static BOOL         bMove       (const std::string_t &csDirPathFrom, const std::string_t &csDirPathTo, const BOOL cbFailIfExists);
            ///< move

        static BOOL         bDelete     (const std::string_t &csDirPath);
            ///< deletion dir which empty
        static BOOL         bTryDelete  (const std::string_t &csDirPath, const size_t cuiAttempts, const ULONG culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static BOOL         bClearForce (const std::string_t &csDirPath);
            ///< detetion all content of dir
        static BOOL         bDeleteForce(const std::string_t &csDirPath);
            ///< detetion dir fnd all content of it

        static BOOL         bFindFiles  (const std::string_t &csDirPath, const std::string_t &cMask, const BOOL cbIsRecurse, std::vector<std::string_t> *pvsFilePathes);
            ///< search files
        static BOOL         bFindDirs   (const std::string_t &csDirPath, const std::string_t &cMask, const BOOL cbIsRecurse, std::vector<std::string_t> *pvsDirPathes);
            ///< search subdirs

    private:
                            CxDir       ();
            ///< constructor
        virtual            ~CxDir       ();
            ///< destructor
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
