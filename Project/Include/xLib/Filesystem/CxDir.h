/**
 * \file  CxDir.h
 * \brief directory
 */


#ifndef xLib_Filesystem_CxDirH
#define xLib_Filesystem_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxConst.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDir :
    private CxNonCopyable
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
        static std::tstring_t sCurrent    ();
            ///< get current
        static void           vSetCurrent (const std::tstring_t &csDirPath);
            ///< set current
        static std::tstring_t sTemp       ();
            ///< get path to system var %Temp%
        static void           vCreate     (const std::tstring_t &csDirPath);
            ///< create
        static void           vCreateForce(const std::tstring_t &csDirPath);
            ///< creation of all dirs that not exists in path
        static void           vCopy       (const std::tstring_t &csDirPathFrom, const std::tstring_t &csDirPathTo, const bool &cbFailIfExists);
            ///< copy
        static void           vMove       (const std::tstring_t &csDirPathFrom, const std::tstring_t &csDirPathTo, const bool &cbFailIfExists);
            ///< move

        static void           vDelete     (const std::tstring_t &csDirPath);
            ///< deletion dir which empty
        static void           vTryDelete  (const std::tstring_t &csDirPath, const size_t &cuiAttempts, const ulong_t &culTimeoutMsec);
            ///< try deleting, max 100 attempts
        static void           vClearForce (const std::tstring_t &csDirPath);
            ///< detetion all content of dir
        static void           vDeleteForce(const std::tstring_t &csDirPath);
            ///< detetion dir fnd all content of it

        static void           vFindFiles  (const std::tstring_t &csDirPath, const std::tstring_t &cMask, const bool &cbIsRecurse, std::vec_tstring_t *pvsFilePathes);
            ///< search files
        static void           vFindDirs   (const std::tstring_t &csDirPath, const std::tstring_t &cMask, const bool &cbIsRecurse, std::vec_tstring_t *pvsDirPathes);
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
