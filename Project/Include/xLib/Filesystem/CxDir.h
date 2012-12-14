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
        explicit               CxDir      (const std::tstring_t &csDirPath);
            ///< constructor
        virtual               ~CxDir      ();
            ///< destructor

        const std::tstring_t & sDirPath   () const;
            ///< directory path

        bool                   bIsExists  ();
            ///< check for existence
        bool                   bIsEmpty   (const std::tstring_t &csPattern = CxConst::xMASK_ALL);
            ///< is empty
        bool                   bIsRoot    ();
            ///< is root
        bool                   bIsDir     ();
            ///< is dir
        void                   vCreate    ();
            ///< create
        void                   vCreatePath();
            ///< creation of all directories that not exists in path
        void                   vCopy      (const std::tstring_t &csDirPathTo, const bool &cbFailIfExists);
            ///< copy
        void                   vMove      (const std::tstring_t &csDirPathTo, const bool &cbFailIfExists);
            ///< move

        void                   vDelete    ();
            ///< deletion dir which empty
        void                   vTryDelete (const size_t &cuiAttempts, const ulong_t &culTimeoutMsec);
            ///< try deleting, max 100 attempts
        void                   vClearPath ();
            ///< deletion all content of dir
        void                   vDeletePath();
            ///< deletion dir find all content of it

        void                   vFindFiles (const std::tstring_t &csPattern,
                                           const bool &cbIsRecursively, std::vec_tstring_t *pvsFilePathes);
            ///< search files
        void                   vFindDirs  (const std::tstring_t &csPattern,
                                           const bool &cbIsRecursively, std::vec_tstring_t *pvsDirPathes);
            ///< search subdirectories

        // static
        static std::tstring_t  sCurrent   ();
            ///< get current
        static void            vSetCurrent(const std::tstring_t &csDirPath);
            ///< set current
        static std::tstring_t  sTemp      ();
            ///< get path to system var %Temp%

    private:
        const std::tstring_t  _m_csDirPath;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxDirH
