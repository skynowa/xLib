/**
 * \file  CxDir.h
 * \brief directory
 */


#ifndef xLib_Filesystem_CxDirH
#define xLib_Filesystem_CxDirH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Common/CxConst.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDir :
    private CxNonCopyable
    /// directory
{
public:
    explicit               CxDir     (std::ctstring_t &csDirPath);
        ///< constructor
    virtual               ~CxDir     ();
        ///< destructor

    std::ctstring_t & dirPath   () const xWARN_UNUSED_RV;
        ///< directory path

    bool_t                   isExists  () xWARN_UNUSED_RV;
        ///< check for existence
    bool_t                   isEmpty   (std::ctstring_t &csPattern = CxConst::xMASK_ALL) xWARN_UNUSED_RV;
        ///< is empty
    bool_t                   isRoot    () xWARN_UNUSED_RV;
        ///< is root
    bool_t                   isDir     () xWARN_UNUSED_RV;
        ///< is dir
    void                   create    ();
        ///< create
    void                   pathCreate();
        ///< creation of all directories that not exists in path
    void                   copy      (std::ctstring_t &csDirPathTo, cbool_t &cbFailIfExists);
        ///< copy
    void                   move      (std::ctstring_t &csDirPathTo, cbool_t &cbFailIfExists);
        ///< move

    void                   remove    ();
        ///< deletion dir which empty
    void                   tryRemove (const size_t &cuiAttempts, culong_t &culTimeoutMsec);
        ///< try deleting, max 100 attempts
    void                   pathClear ();
        ///< deletion all content of dir
    void                   pathDelete();
        ///< deletion dir find all content of it

    void                   filesFind (std::ctstring_t &csPattern,
                                      cbool_t &cbIsRecursively, std::vec_tstring_t *pvsFilePathes);
        ///< search files
    void                   dirsFind  (std::ctstring_t &csPattern,
                                      cbool_t &cbIsRecursively, std::vec_tstring_t *pvsDirPathes);
        ///< search subdirectories

    // static
    static std::tstring_t  current   () xWARN_UNUSED_RV;
        ///< get current
    static void            setCurrent(std::ctstring_t &csDirPath);
        ///< set current
    static std::tstring_t  temp      () xWARN_UNUSED_RV;
        ///< get path to system var %Temp%

private:
    std::ctstring_t   _m_csDirPath;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxDirH
