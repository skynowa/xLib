/**
 * \file   CxFinder.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Filesystem/CxFileType.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFinder :
    public CxNonCopyable
    ///< file system finder
{
public:
                        CxFinder   (std::ctstring_t &csRootDirPath,
                                    std::ctstring_t &csShellFilter);
        ///< constructor
    virtual            ~CxFinder   ();
        ///< destructor

    std::ctstring_t &   rootDirPath() const xWARN_UNUSED_RV;
        ///< root directory path
    std::ctstring_t &   shellFilter() const xWARN_UNUSED_RV;
        ///< shell wild card filter
    std::tstring_t      entryName  () const xWARN_UNUSED_RV;
        ///< entry name
    std::tstring_t      entryPath  () const xWARN_UNUSED_RV;
        ///< entry path
    CxFileType::types_t fileTypes  () const xWARN_UNUSED_RV;
        ///< file attributes

    bool_t              isValid    () const xWARN_UNUSED_RV;
        ///< is valid handle
    bool_t              moveNext   () xWARN_UNUSED_RV;
        ///< move next entry
    void_t              close      ();
        ///< close search

    static void_t       dirs       (std::ctstring_t    &csRootDirPath,
                                    std::ctstring_t    &csShellFilter,
                                    cbool_t            &cbIsRecursively,
                                    std::vec_tstring_t *pvsDirPaths);
        ///< search subdirectories
    static void_t       files      (std::ctstring_t    &csRootDirPath,
                                    std::ctstring_t    &csShellFilter,
                                    cbool_t            &cbIsRecursively,
                                    std::vec_tstring_t *pvsFilePaths);
        ///< search files

private:
    struct _SEntry {
    #if xOS_ENV_WIN
        HANDLE           hHandle;
        WIN32_FIND_DATA  fdData;

        _SEntry() :
            hHandle(xNATIVE_HANDLE_INVALID),
            fdData ()
        {}
    #else
        DIR             *pHandle;
        dirent          *pdrData;

        _SEntry() :
            pHandle(NULL),
            pdrData(NULL)
        {}
    #endif
    };

    typedef _SEntry _entry_t;
        ///< entry

    _entry_t            _m_enEnrty;        ///< entry handle
    std::ctstring_t     _m_csRootDirPath;  ///< root directory path
    std::ctstring_t     _m_csShellFilter;  ///< shell wild card filter
    bool_t              _m_bIsMoveFirst;   ///< is first movement

    bool_t              _moveFirst () xWARN_UNUSED_RV;
        ///< move first entry
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
