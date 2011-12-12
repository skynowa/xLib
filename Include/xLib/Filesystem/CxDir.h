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
        static bool           bIsExists   (const std::tstring_t &csDirPath);
            ///< check for existence
        static bool           bIsEmpty    (const std::tstring_t &csDirPath, const std::tstring_t &csMask = CxConst::xMASK_ALL);
            ///< is empty
        static bool           bIsRoot     (const std::tstring_t &csDirPath);
            ///< is root
        static bool           bIsDir      (const std::tstring_t &csDirPath);
            ///< is dir
        static std::tstring_t sGetCurrent ();
            ///< get current
        static bool           bSetCurrent (const std::tstring_t &csDirPath);
            ///< set current
        static std::tstring_t sGetTemp    ();
            ///< get path to system var %Temp%
        static bool           bCreate     (const std::tstring_t &csDirPath);
            ///< create
        static bool           bCreateForce(const std::tstring_t &csDirPath);
            ///< creation of all dirs that not exists in path
        static bool           bCopy       (const std::tstring_t &csDirPathFrom, const std::tstring_t &csDirPathTo, const bool cbFailIfExists);
            ///< copy
        static bool           bMove       (const std::tstring_t &csDirPathFrom, const std::tstring_t &csDirPathTo, const bool cbFailIfExists);
            ///< move

        static bool           bDelete     (const std::tstring_t &csDirPath);
            ///< deletion dir which empty
        static bool           bTryDelete  (const std::tstring_t &csDirPath, const size_t cuiAttempts, const ulong_t culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static bool           bClearForce (const std::tstring_t &csDirPath);
            ///< detetion all content of dir
        static bool           bDeleteForce(const std::tstring_t &csDirPath);
            ///< detetion dir fnd all content of it

        static bool           bFindFiles  (const std::tstring_t &csDirPath, const std::tstring_t &cMask, const bool cbIsRecurse, std::vector<std::tstring_t> *pvsFilePathes);
            ///< search files
        static bool           bFindDirs   (const std::tstring_t &csDirPath, const std::tstring_t &cMask, const bool cbIsRecurse, std::vector<std::tstring_t> *pvsDirPathes);
            ///< search subdirs

    private:
                              CxDir       ();
            ///< constructor
        virtual              ~CxDir       ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxDirH
