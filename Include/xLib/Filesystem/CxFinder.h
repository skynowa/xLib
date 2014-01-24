/**
 * \file   CxFinder.h
 * \brief
 */


#pragma once

#ifndef xLib_CxFinderH
#define xLib_CxFinderH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
#include <xLib/Filesystem/CxFileType.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, filesystem)

class CxFinder
    ///< file system finder
{
public:
                        CxFinder(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter);
        ///< constructor
    virtual            ~CxFinder();
        ///< destructor

    std::ctstring_t &   rootDirPath() const xWARN_UNUSED_RV;
        ///< root directory path
    std::ctstring_t &   shellFilter() const xWARN_UNUSED_RV;
        ///< shell wild card filter
    std::tstring_t      entryName() const xWARN_UNUSED_RV;
        ///< entry name
    std::tstring_t      entryPath() const xWARN_UNUSED_RV;
        ///< entry path
    CxFileType::types_t fileTypes() const xWARN_UNUSED_RV;
        ///< file attributes

    bool_t              isValid() const xWARN_UNUSED_RV;
        ///< is valid handle
    bool_t              moveNext() xWARN_UNUSED_RV;
        ///< move next entry
    void_t              close();
        ///< close search

    static
    void_t              dirs(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter,
                            cbool_t &isRecursively, std::vec_tstring_t *dirPaths);
        ///< search subdirectories
    static
    void_t              files(std::ctstring_t &rootDirPath, std::ctstring_t &shellFilter,
                            cbool_t &isRecursively, std::vec_tstring_t *filePaths);
        ///< search files

private:
    struct _Entry
    {
    #if   xOS_ENV_WIN
        HANDLE          handle;
        WIN32_FIND_DATA data;

        _Entry() : handle(xNATIVE_HANDLE_INVALID), data() {}
    #elif xOS_ENV_UNIX
        DIR *           handle;
        dirent          data;

        _Entry() : handle(NULL), data() {}
    #endif
    };

    _Entry              _entry;        ///< entry handle
    std::ctstring_t     _rootDirPath;  ///< root directory path
    std::ctstring_t     _shellFilter;  ///< shell wild card filter
    bool_t              _isMoveFirst;   ///< is first movement

    bool_t              _moveFirst() xWARN_UNUSED_RV;
        ///< move first entry

    xNO_COPY_ASSIGN(CxFinder)
};

xNAMESPACE2_END(xlib, filesystem)
//-------------------------------------------------------------------------------------------------
#include "CxFinder.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxFinderH
